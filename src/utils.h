#ifndef UTILS_H
#define UTIls_H 1

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// for holding each line of the string text
// len is number of character excluding \0
// It is a linked-list
struct strbuf{
  uint64_t len;  // the length of the current string
  char *sptr; // string pointer
  struct strbuf* next;
};

// for holding the whole file of the text
// len is number of strbuf presented in the linked-lisE
// struct textbuf{
//   uint64_t len;
//   // a pointer to strbuf, the start of the linked-list
//   struct strbuf *strings;
// };

void strbuf_init(struct strbuf **);
void strbuf_append(struct strbuf *, char *, int);
int strbuf_is_empty_string(struct strbuf *);
int strbuf_is_linebreak(struct strbuf *);
int strbuf_is_space(struct strbuf *);
void strbuf_delete_between(struct strbuf *, struct strbuf *);
void strbuf_remove_next(struct strbuf *);
void strbuf_free(struct strbuf *);
void print_strbuf_list(struct strbuf *);

// void textbuf_init(struct textbuf *);
// void textbuf_append(struct textbuf *, struct strbuf *);
// void textbuf_free(struct textbuf *);

void exit_program(char *, int);

#ifndef _POSIX_C_SOURCE 
#define _POSIX_C_SOURCE -1
#endif

#if !_POSIX_C_SOURCE >= 200809L || ! defined _GNU_SOURCE 
// My own implementation of strnlen_s()
// return the number of the byte pointed to by s, excluding '\0' but 
// at most len
size_t strnlen_s(const char *s, size_t maxlen);
#endif

// an implementation of getline()
// getline() is included in 
           // Since glibc 2.10:
           //     _POSIX_C_SOURCE >= 200809L
           // Before glibc 2.10:
           //     _GNU_SOURCE

#if !defined _POSIX_C_SOURCE || !defined _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
ssize_t getline(char **restrict buffer, size_t *restrict size,
                FILE *restrict fp);
#endif


#endif // for utils.h
