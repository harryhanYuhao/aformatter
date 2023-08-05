#include "utils.h"
#include "globals.h"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

// break all input into tokens and read into strbuf
// any character between spaces or new line are considered a token 
// (excluding spaces and new lines)
// a single space and a single linebreak are considered as tokens
// struct strbuf* tbptr must be a pointer pointed to an initialized strbuf
int read_to_strbuf(struct strbuf* sbptr, char * name)
{
  int fd = open(name, O_RDONLY);

  struct strbuf *cur = sbptr;

  char tmp = ' ';
  char pre; 
  while (read(fd, &tmp, 1)>0){
    int newList = 0;
    if (tmp == ' ' || tmp == '\n' || tmp == '\t'|| pre == ' ' || pre == '\n' || pre == '\t')
      newList = 1;
    if(newList){
      newList = 0;
      struct strbuf *pre_strbuf = cur;
      strbuf_init(&cur);
      pre_strbuf->next = cur;
    }
    strbuf_append(cur, &tmp, 1);
    pre = tmp;
  }

  if (close(fd)==-1){
    char errorString[64]; 
    snprintf(errorString, 64, "fail to open file %s", name);
    exit_program(errorString, -1);
  }
  return 0;
}

// remove all spaces in a line if this line consist of only spaces
// the line is retained 
void strip_trailing_space(struct strbuf * sbptr)
{
  struct strbuf *cur = sbptr;
  struct strbuf *poke = sbptr;

  for (;cur->next != NULL; cur = cur->next){
    poke = cur->next;
    while (strbuf_is_space(poke)){
      poke = poke->next;
    }
    if (strbuf_is_linebreak(poke))
      strbuf_delete_between(cur, poke);
  }
}


void strip_initial_space(struct strbuf * sbptr)
{
  struct strbuf *cur = sbptr;
  struct strbuf *poke = sbptr;
  //
  // first take care of the space at the beginning of the document
  while (strbuf_is_space(cur)){
    // self delete make cur equal to that of cur->next
    strbuf_self_delete(cur);
  }

  for (;cur->next != NULL; cur = cur->next){
    if (!strbuf_is_linebreak(cur))
      continue;
    poke = cur->next;
    while (strbuf_is_space(poke)){
      poke = poke->next;
    }
    strbuf_delete_between(cur, poke);
  }
}

// remove extra line breaks if there is three or more consecutive line breaks
// reduce number of consecutive linebreaks to two
void strip_repetitive_linebreaks(struct strbuf * sbptr)
{
  struct strbuf * cur = sbptr;
  while (1){
    if (strbuf_is_linebreak(cur)){
      while 
        (strbuf_is_linebreak(cur->next) && strbuf_is_linebreak(cur->next->next))
        strbuf_remove_next(cur);
    }
    if (cur->next==NULL)
      break;
    // to avoid segfault:
    // can not be written as if(cur->next == NULL || cur->next->next==NULL)
    if (cur->next->next==NULL)
      break;
    cur = cur->next;
  }
}

/// assigne token code for each strbuf .
void strbuf_tokenisation(struct strbuf *sbptr)
{
  struct strbuf *cur = sbptr;
  int tmp;
  while (cur->next!=NULL){
    if (cur->len == 0 || cur -> sptr == NULL);
      // note strbuf_is_comment return 0 if it is not comment 
      // it return a positive int if it is comment, 
      // the int tells how long the comment is (in terms of tokens)
      // tmp = the number of tokens the comments consists of, not including
      // the comment sign
    else if ((tmp = strbuf_is_comment(cur))){
      cur->token = 0; 
      for (int i = 0; i < tmp-1; i++){
        strbuf_merge(cur, cur->next);
      }
    }
    else if (strbuf_is_section(cur)){
      cur->token = 1;
    }
    else if (strbuf_is_space(cur)){
      cur->token = 32;
    } else if (strbuf_is_linebreak(cur)){
      cur->token = 10;
    } else if (cur->token == -1){
      cur -> token = 2;
    }
    cur=cur->next;
  }
}

// the initial sbptr may contain null pointers
// check and remove all null elements in the list

void format_strbuf_list(struct strbuf **sbpp)
{

  struct strbuf * sbp = *sbpp;
  strip_trailing_space(sbp);
  strip_initial_space(sbp);
  strip_repetitive_linebreaks(sbp);
  
  strip_null_strbuf(sbpp);
  
  strbuf_tokenisation(sbp);
}

// create a linked-list with size of ten
// each holding different ascii character
void test(void){
  struct strbuf **list = (struct strbuf **) calloc(10, sizeof(struct strbuf**));
  for (int i = 0; i < 10; i++){
    struct strbuf *tmp;
    strbuf_init(&tmp);
    list[i] = tmp;
  }
  for (int i = 0; i < 9; i++){
    list[i]->next = list[i+1];
  }
  for (int i = 0; i < 10; i++){
    char tmp = 40+i;
    strbuf_append(list[i], &tmp, 1);
  }
  strbuf_delete_between(list[0], list[2]);

  print_strbuf_list(*list);
}

int main(int argc, char * argv[])
{
  // test();
  if (argc <= 1){
    printf("%s\n", "No argument given!");
    return 0;
  }

  struct strbuf *sbp;
  strbuf_init(&sbp);          

  read_to_strbuf(sbp, argv[1]);
  format_strbuf_list(&sbp);             

  print_strbuf_list(sbp);  
  debug_print(sbp);

  return 0;
}
