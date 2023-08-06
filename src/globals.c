#include "utils.h"

void debug_track(void)
{
  return;
}

int comment_string_length;
char comment_string_first_char;
char comment_string_second_char;

void init_global_variables(void){
  comment_string_length = 1;
  comment_string_first_char = '#';
  comment_string_second_char = ';';
}
