#include "utils.h"

void strbuf_init(struct strbuf **sb)
{
  *sb = (struct strbuf *)calloc(1, sizeof(struct strbuf)); 
  (*sb)->len=0;
  (*sb)->sptr = NULL;
  (*sb)->next = NULL;
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

// check if strbuf contains nothing.

int strbuf_is_empty_string(struct strbuf *sb)
{
  if (sb->len==0)
    return 1;
  return 0;
}

// check if strbuf only contains linebreak
int strbuf_is_linebreak(struct strbuf *sb){
  if(sb->len == 1 && *(sb->sptr) == 10)
    return 1;
  return 0;
}

int strbuf_is_space(struct strbuf *sb){
  if(sb->len == 1 && *(sb->sptr) == ' ')
    return 1;
  return 0;
}

void strbuf_free(struct strbuf *sb)
{
  sb->len=0;
  free(sb->sptr);
  sb->sptr = NULL;
}

// remove the next of the linked list, while linking the first the the next's next
void strbuf_remove_next(struct strbuf * sb)
{
  if (sb->next == NULL)
    return;
  struct strbuf * nextNext = sb->next->next;
  strbuf_free(sb->next);
  sb->next = nextNext;
}

/// TEST: PASSED PRELIMILARY TESTING
// delete from begin (non inclusive) to end (non-inclusive)
void strbuf_delete_between(struct strbuf *begin, struct strbuf *end)
{
  struct strbuf *cur = begin->next;
  while (cur != end){
    struct strbuf *next = cur ->next;
    strbuf_free(cur);
    cur = next;
  }
}

void print_strbuf_list(struct strbuf *sb){
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
