#include "utils.h"

void debug_track(void)
{
  return;
}

int comment_string_length;
char comment_string_first_char;
char comment_string_second_char;
struct strbuf *global_tab;
struct strbuf *global_1space;

void init_global_variables(void){
  comment_string_length = 1;
  comment_string_first_char = '#';
  comment_string_second_char = ';';

  strbuf_init(&global_tab);
  global_tab->len = 4;
  global_tab->sptr = (char *) calloc(4, 1);
  char spaces[12] = "            ";
  memmove(global_tab->sptr, spaces, 4);

  strbuf_init(&global_1space);
  global_tab->len = 1;
  global_tab->sptr = (char *) calloc(1, 1);
  memmove(global_tab->sptr, spaces, 1);
}
