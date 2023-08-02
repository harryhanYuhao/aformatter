#include "utils.h"
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

void format_strbuf_list(struct strbuf *sbptr)
{

  strip_trailing_space(sbptr);
  strip_initial_space(sbptr);

  // remove extra line breaks if there is three consecutive line breaks
  struct strbuf * cur;
  cur = sbptr;
  while(cur->next!=NULL){
    if (strbuf_is_linebreak(cur)){
      while (strbuf_is_linebreak(cur->next)&&strbuf_is_linebreak(cur->next->next))
        strbuf_remove_next(cur);
    }
    cur=cur->next; 
  }
}

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

  strbuf_delete_between(*list, list[3]);
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
  format_strbuf_list(sbp);             

  print_strbuf_list(sbp);  
                               
  return 0;
}
