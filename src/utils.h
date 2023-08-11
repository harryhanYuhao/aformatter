#ifndef UTILS_H
#define UTIls_H 1

// for open() syscall in int read_to_strbuf()
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "globals.h"

void strbuf_init(struct strbuf **);
struct strbuf *get_n_strbuf(struct strbuf *, int);
void strbuf_append(struct strbuf *, char *, int);
void strbuf_merge(struct strbuf *, struct strbuf *);
void strbuf_self_delete(struct strbuf *);
int strbuf_is_null_strbuf(struct strbuf *);
int strbuf_is_linebreak(struct strbuf *);
int strbuf_is_space(struct strbuf *);
int strbuf_is_section(struct strbuf *);
int strbuf_is_comment(struct strbuf *);
int strbuf_is_double_quotation_mark(struct strbuf *);
int strbuf_is_single_quotation_mark(struct strbuf *);
int strbuf_is_label(struct strbuf *);
void strbuf_insert_after(struct strbuf *, struct strbuf *);
void strbuf_presert_before(struct strbuf **, struct strbuf *);
void strbuf_presert_n_spaces_before(struct strbuf **, int);
void strbuf_insert_n_spaces_after(struct strbuf *, int);
void strbuf_delete_between(struct strbuf *, struct strbuf *);
int strip_null_strbuf(struct strbuf *);
void strbuf_remove_next(struct strbuf *);
void strbuf_free(struct strbuf *);
void strbuf_free_list(struct strbuf *);
void save_to_file(char *, struct strbuf *);
void print_strbuf_list(struct strbuf *);
void debug_print(struct strbuf *);

int read_to_strbuf(struct strbuf *, char*);

// string parsing and manipulation

// passing a null-terminated string. 
// return 1 for - flags. 2 for -- flags, and 3 for filename, 0 for nothing
int determine_flag_type(char *);

void exit_program(char *, int);

void debug_track(void);
#endif // for utils.h
