#ifndef GLOBALS_H
#define GLOBALS_H 1

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 1

#include <stdint.h>
// token status:
// -2 to be deleted 
// -1 undefined
// 0 comments: it belowns to comments
// 1 section header
// 2 keywords, register, etc
// 3 labels
// between quotation mark
// 68 to be delted, (68 is ascii code of D)
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
// len is number of strbuf presented in the linked-list
// struct textbuf{
//   uint64_t len;
//   // a pointer to strbuf, the start of the linked-list
//   struct strbuf *strings;
// };
// the sole purpose of this struct is to hold global configs

struct config {  
  int COMMENT_STRING_LENGTH;
  char COMMENT_STRING_FIRST_CHAR;
  char COMMENT_STRING_SECOND_CHAR;
};

extern struct config CF; // config
extern struct config *PTCF;  // pointer to config
extern struct strbuf *FILENAMES;

void init_global_variables(void);

#endif // for GLOBALS_H
