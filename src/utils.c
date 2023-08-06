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
void strbuf_copy(struct strbuf *sb1, struct strbuf *sb2)
{
  if (sb1 == NULL || sb2 == NULL)
    return;
  sb1->len = sb2->len;
  sb1->token = sb2->token;
  sb1->next = sb2->next;
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
  if(sb->len == 1 && *(sb->sptr) == ' ')
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
int strbuf_is_comment(struct strbuf *sptr){
  int res = 0;
  struct strbuf *cur = sptr;
  if (comment_string_length == 1){
    if(cur->len == 1 && *(cur->sptr) == comment_string_first_char){
      res = strbuf_to_endofline(cur);
    }
  }
  else if (comment_string_length == 2){
    if(cur->len == 1 && *(cur->sptr) == comment_string_first_char && *(cur->next->sptr) == comment_string_second_char)
    {
      res = strbuf_to_endofline(cur);
    }
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

// TEST: PASSED PRELIMILARY TESTING
// delete from begin (non inclusive) to end (non-inclusive)
void strbuf_delete_between(struct strbuf *begin, struct strbuf *end)
{
  struct strbuf *cur = begin;
  while (cur->next != end){
    strbuf_remove_next(cur);
  }
}

// Starting from sbptr, delete all null strbuf
// if sbptr itself is null, modified it so that it become the closest non-null strbuf
int strip_null_strbuf(struct strbuf * sbp)
{
  int res = 0;
  struct strbuf *cur = sbp;
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

void print_strbuf_list(struct strbuf *sb)
{
  struct strbuf *cur = sb;
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
}

void debug_print(struct strbuf *sb)
{
  struct strbuf *cur = sb;
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

void exit_program(char *s, int exit_num)
{
  if (exit_num == 0)
    exit(0);  // from stdlib.h

  perror(s); // stdio.h
  exit(1);
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
