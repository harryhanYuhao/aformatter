#include "utils.h"
#include "globals.h"

void strbuf_init(struct strbuf **sb)
{
  *sb = (struct strbuf *)calloc(1, sizeof(struct strbuf)); 
  (*sb)->len=0;
  (*sb)->sptr = NULL;
  (*sb)->next = NULL;
  (*sb)->token = -1;
}

// needs improvement:
// the append shall terminate upon reading of "\0"
void strbuf_append(struct strbuf * sb, char * in, int len)
{
 char *new = realloc(sb->sptr, len + sb->len);
  if (new == NULL)
    exit_program("Fail to realloc memory for function sbAppend", 1);
  memcpy(&new[sb->len], in, len); // From <string.h>
  sb->sptr = new;
  sb->len += len;
}

// merge two strbuf, the first shall preceed the second
void strbuf_merge(struct strbuf *sb1, struct strbuf *sb2)
{
  if  (sb1->next != sb2){ 
    exit_program("strbuf_merged failed, the second strbuf does not follows the first", -1);
  }
  strbuf_append(sb1, sb2->sptr, sb2->len);
  sb1->next = sb2->next;
  strbuf_free(sb2);
}

// Copy the content of sb2 to sb1. sb1 and sb2 are independent. Free sb1->sptr
// both must be initilized
void strbuf_copy(struct strbuf *sb1, struct strbuf *sb2)
{
  if (sb1 == NULL || sb2 == NULL)
    return;
  sb1->len = sb2->len;
  sb1->token = sb2->token;
  sb1->next = sb2->next;
  if (sb1->sptr != NULL)
    free(sb1->sptr);
  sb1->sptr = (char *)calloc(sb2->len, 1);
  memmove(sb1->sptr, sb2->sptr, sb2->len);
}

// Make sb exactly the same as sb->next, and free appropraite memory
// as if sb is deleted
void strbuf_self_delete(struct strbuf *sb)
{
  if (sb == NULL) 
    return;
  struct strbuf *tmp = sb->next;
  strbuf_copy(sb, sb->next); 
  strbuf_free(tmp);
}

// insert content after location
// both must be initialized
void strbuf_insert_after(struct strbuf *location, struct strbuf *content)
{
  content->next = location->next;
  location->next = content;
}

// both must be initialzied
// this function make location hold the value of content, 
// which points to the content, and content inserted after the location,
// pointing to the next appropraite struct
// to use in loop like while (cur->next != NULL) {...; cur= cur->next}
// when using it, it requires to pass int struct strbuf **
// the *location may be changed, the the struct would contain exactly the same element as.
void strbuf_presert_before(struct strbuf **location, struct strbuf * content)
{
  struct strbuf * cur = *location;

  if (cur == NULL || content == NULL)
    exit_program("arguments not initialized for void strbuf_presert_before()", -1);
  struct strbuf *tmp;
  strbuf_init(&tmp);
  strbuf_copy(tmp, cur);

  // we have copied the content, the next pointer is not adjusted
  strbuf_copy(cur, content);
  cur->next = tmp->next;
  strbuf_copy(content, tmp);
  strbuf_insert_after(cur, content);
  
  *(location) = cur->next;
}

void strbuf_presert_n_spaces_before(struct strbuf **sb, int n)
{
  if (n>12)
    exit_program("strbuf_presert_n_spaces_before() failed! Maximum numver of space is 12", 1);
    
  struct strbuf *spaces;
  strbuf_init(&spaces);
  spaces->len = n;
  spaces->sptr = (char *) calloc(n, 1);
  char tmp[12] = "            ";
  memmove(spaces->sptr, tmp, n);
  strbuf_presert_before(sb, spaces);
}


void strbuf_insert_n_spaces_after(struct strbuf *sb, int n)
{
  if (n>12)
    exit_program("strbuf_presert_n_spaces_before() failed! Maximum numver of space is 12", 1);

  struct strbuf *spaces;
  strbuf_init(&spaces);
  spaces->len = n;
  spaces->sptr = (char *) calloc(n, 1);
  char tmp[12] = "            ";
  memmove(spaces->sptr, tmp, n);
  strbuf_insert_after(sb, spaces);
}

// check if strbuf contains nothing.

int strbuf_is_null_strbuf(struct strbuf *sb)
{
  if (sb->next == NULL)
    return 1;
  if (sb->len==0)
    return 1;
  return 0;
}

// check if strbuf only contains linebreak
int strbuf_is_linebreak(struct strbuf *sb){
  if (sb == NULL)
    return 0;
  if(sb->len == 1 && *(sb->sptr) == 10)
    return 1;
  return 0;
}

int strbuf_is_space(struct strbuf *sb){
  if (sb == NULL)
    return 0;
  // 32 space, 9 horizantal tab
  if(sb->len == 1 && (*(sb->sptr) == 32 || *(sb->sptr) == 9))
    return 1;
  return 0;
}

int strbuf_is_section(struct strbuf *sb)
{
  if (sb == NULL || sb->sptr == NULL)
    return 0;
  if(sb->len > 1 && *(sb->sptr) == '.')
    return 1;
  return 0;
}


int strbuf_is_label(struct strbuf *sb)
{
  if (sb == NULL || sb->sptr == NULL)
    return 0;
  if (sb->len>1 && (sb->sptr)[sb->len-1] == ':')
    return 1;
  return 0;
}

// return the number of strbuf there are between sptr and \n or EOF
// exclusive on both end
// (cur) !a! \n wou return 1
static int strbuf_to_endofline(struct strbuf *sptr){
  int counter = 0;
  struct strbuf *cur = sptr;
  while (cur->next != NULL){
    if (*(cur->sptr) == 10){
      break;
    }
    ++counter;
    cur = cur->next;
  }
  return counter;
}

  // note strbuf_is_comment return 0 if it is not comment 
  // it return a positive int if it is comment, 
  // the int tells how long the comment is (in terms of tokens)
  // tmp = the number of tokens the comments consists of, including 
  // the comment sign
// exclusive on both end
// neither the line break token nor the current token counts
int strbuf_is_comment(struct strbuf *sb){
  int res = 0;
  struct strbuf *cur = sb;
  if (COMMENT_STRING_LENGTH == 1){
    if(cur->len == 1 && *(cur->sptr) == COMMENT_STRING_FIRST_CHAR){
      res = strbuf_to_endofline(cur);
    }
  }
  else if (COMMENT_STRING_LENGTH == 2){
    if(cur->len == 1 && *(cur->sptr) == COMMENT_STRING_FIRST_CHAR && *(cur->next->sptr) == COMMENT_STRING_SECOND_CHAR)
    {
      res = strbuf_to_endofline(cur);
    }
  }
  return res;
}

static int strbuf_to_next_double_quotation(struct strbuf *sptr){
  int counter = 0;
  struct strbuf *cur = sptr;
  while (cur->next != NULL){
    if (*(cur->sptr) == '"'){
      break;
    }
    ++counter;
    cur = cur->next;
  }
  return counter;
}

int strbuf_is_double_quotation_mark(struct strbuf *sb){
  int res = 0;
  struct strbuf *cur = sb;
  if(cur->len == 1 && *(cur->sptr) == '"'){
    res = strbuf_to_next_double_quotation(cur->next);
  }
  return res;
}


static int strbuf_to_next_single_quotation(struct strbuf *sptr){
  int counter = 0;
  struct strbuf *cur = sptr;
  while (cur->next != NULL){
    if (*(cur->sptr) == '\''){
      break;
    }
    ++counter;
    cur = cur->next;
  }
  return counter;
}

int strbuf_is_single_quotation_mark(struct strbuf *sb){
  int res = 0;
  struct strbuf *cur = sb;
  if(cur->len == 1 && *(cur->sptr) == '\''){
    res = strbuf_to_next_single_quotation(cur->next);
  }
  return res;
}

void strbuf_free(struct strbuf *sb)
{
  sb->len=0;
  free(sb->sptr);
  sb->sptr = NULL;
  free(sb);
}

// remove the next of the linked list, while linking the first the the next's next
void strbuf_remove_next(struct strbuf * sb)
{
  // if sb is the last in the list
  if (sb->next == NULL)
    return;
  // if sb is the second last in the list
  if (sb->next->next == NULL){
    strbuf_free(sb->next);
    sb->next = NULL;
    return;
  }
  struct strbuf * nextNext = sb->next->next;
  strbuf_free(sb->next);
  sb->next = nextNext;
}

// delete from begin (non-inclusive) to end (non-inclusive)
void strbuf_delete_between(struct strbuf *begin, struct strbuf *end)
{
  struct strbuf *cur = begin;
  while (cur->next != end){
    strbuf_remove_next(cur);
  }
}

// Starting from sb, delete all null strbuf
// if sb itself is null, modified it so that it become the closest non-null strbuf
// return the number fo null strbuf stripped.
int strip_null_strbuf(struct strbuf * sb)
{
  int res = 0;
  struct strbuf *cur = sb;
  while(cur->next != NULL){
    if (strbuf_is_null_strbuf(cur)){
      ++res;
      strbuf_self_delete(cur);
    }
    else{
      cur = cur->next;
    }
  }
  return res;
}

// write the content of the linked list to file name.
// if `name` does not exist, it will be created
// if `name` already exists, it will be truncated
void save_to_file(char *name, struct strbuf *sbptr)
{
  int fd = open(name, O_TRUNC|O_RDWR|O_CREAT, 00666);

  struct strbuf *cur = sbptr;
  while (1){
    if (cur->sptr!=NULL){
      // syscall, requires unistd.h
      write(fd, cur->sptr, cur->len);
    }
    if (cur->next==NULL)
      break;
    cur=cur->next;
  }

  if (close(fd)==-1){
    char errorString[64]; 
    snprintf(errorString, 64, "fail to open file %s", name);
    exit_program(errorString, -1);
  }
}

void print_strbuf_list(struct strbuf *sb)
{
  struct strbuf *cur = sb;
  while (1){
    if (cur->sptr!=NULL){
      // syscall, requires unistd.h
      write(STDOUT_FILENO, cur->sptr, cur->len);
    }
    if (cur->next==NULL)
      break;
    cur=cur->next;
  }
}

void debug_print(struct strbuf *sb)
{
  struct strbuf *cur = sb;
  // print all tokens with ! to separate them
  while (1){
    if (cur->sptr!=NULL){
      // syscall, requires unistd.h
      char tmp [] = {'!'};
      write(STDOUT_FILENO, tmp, 1);
      write(STDOUT_FILENO, cur->sptr, cur->len);
    }
    if (cur->next==NULL)
      break;
    cur=cur->next;
  }
  cur = sb;
  // print the length of the token with ! to separate them
  while (1){
    if (cur->sptr!=NULL){
      // syscall, requires unistd.h
      if (*(cur->sptr)==10){
        write(STDOUT_FILENO, "!\\n\n", 4);
      } else{
        char tmp[5];
        snprintf(tmp, 5, "!%lu", cur->len);
        write(STDOUT_FILENO, tmp, strlen(tmp));
      }
    }
    if (cur->next==NULL)
      break;
    cur=cur->next;
  }
}

// load file `name` intoo linked list and break them to 
// preliminary tokens
// break all input into tokens and read into strbuf
// any character between spaces or new line are considered a token 
// (excluding spaces and new lines)
// a single space and a single linebreak are considered as tokens
// struct strbuf* tbptr must be a pointer pointed to an initialized strbuf
int read_to_strbuf(struct strbuf* sb, char * name)
{
  int fd = open(name, O_RDONLY);

  struct strbuf *cur = sb;
  struct strbuf *initial = sb;

  char tmp = ' ';
  char pre= '\0'; 
  while (read(fd, &tmp, 1)>0){
    int newList = 0;
    // note in the algorithm the first strbuf will be a null strbuf
    // it needs to be removed 
    if (tmp == ' ' || tmp == '\n' || tmp == '\t'|| pre == ' ' || pre == '\n' || pre == '\t' || tmp == '"' || pre == '"')
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

  // During read process null strbuf may be introduced.
  strip_null_strbuf(initial);

  if (close(fd)==-1){
    char errorString[64]; 
    snprintf(errorString, 64, "fail to open file %s", name);
    exit_program(errorString, -1);
  }
  return 0;
}


// if exit_num > 0, there is no system error 
// or system error was catched by code.
void exit_program(char *s, int exit_num)
{
  if (exit_num == 0)
    exit(0);  // from stdlib.h
  if (exit_num < 0){
    perror(s); // stdio.h
    exit(1);
  } else{
    printf("%s\n", s);
    exit(1);
  }
}

// an implementation of getline()
// getline() is included in see man getline(3) which contains the following
//
// Since glibc 2.10:
//     _POSIX_C_SOURCE >= 200809L
// Before glibc 2.10:
//     _GNU_SOURCE
#ifndef _POSIX_C_SOURCE 
#define _POSIX_C_SOURCE -1
#endif

#if !_POSIX_C_SOURCE >= 200809L || ! defined _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
ssize_t getline(char **restrict buffer, size_t *restrict size,
                FILE *restrict fp) {
  register int c;
  register char *cs = NULL;

  if (cs == NULL) {
    register int length = 0;
    while ((c = getc(fp)) != EOF) {
      cs = (char *)realloc(cs, ++length + 1);
      if ((*(cs + length - 1) = c) == '\n') {
        *(cs + length) = '\0';
        *buffer = cs;
        break;
      }
    }
    return (ssize_t)(*size = length);
  } else {
    while (--(*size) > 0 && (c = getc(fp)) != EOF) {
      if ((*cs++ = c) == '\n')
        break;
    }
    *cs = '\0';
  }
  return (ssize_t)(*size = strlen(*buffer));
}
#endif
