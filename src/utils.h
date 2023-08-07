#ifndef UTILS_H
#define UTIls_H 1

// for open() syscall in int read_to_strbuf()
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// token status:
// -1 undefined
// 0 comments: it belowns to comments
// 1 section header
// 2 keywords, register, etc
// 3 labels
// 10 new line
// 32 space 
// 100 : it is the first of the line 
// 101 : it is the section header at the fisrt of the line

// for holding each line of the string text
// len is number of character excluding \0
// It is a linked-list
struct strbuf{
  uint64_t len;  // the length of the current string
  char *sptr; // string pointer
  struct strbuf* next;
  char token;  // record the token status of this string
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
void strbuf_merge(struct strbuf *, struct strbuf *);
void strbuf_self_delete(struct strbuf *);
int strbuf_is_null_strbuf(struct strbuf *);
int strbuf_is_linebreak(struct strbuf *);
int strbuf_is_space(struct strbuf *);
int strbuf_is_section(struct strbuf *);
int strbuf_is_comment(struct strbuf *);
int strbuf_is_label(struct strbuf *);
void strbuf_insert_after(struct strbuf *, struct strbuf *);
void strbuf_presert_before(struct strbuf **, struct strbuf *);
void strbuf_presert_n_spaces_before(struct strbuf **, int);
void strbuf_insert_n_spaces_after(struct strbuf *, int);
void strbuf_delete_between(struct strbuf *, struct strbuf *);
int strip_null_strbuf(struct strbuf *);
void strbuf_remove_next(struct strbuf *);
void strbuf_free(struct strbuf *);
void save_to_file(char *, struct strbuf *);
void print_strbuf_list(struct strbuf *);
void debug_print(struct strbuf *);

int read_to_strbuf(struct strbuf *, char*);

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
