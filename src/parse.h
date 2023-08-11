#ifndef PARSE_H
#define PARSE_H 1

void strip_trailing_space(struct strbuf *);
void strip_initial_space(struct strbuf *);
void strip_repetitive_linebreaks(struct strbuf *);
void strbuf_tokenisation(struct strbuf *);
void delete_tobe_deleted(struct strbuf *);
void format_insert_spaces(struct strbuf*);

#endif  // for PARSE_H
