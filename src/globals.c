#include "utils.h"

void debug_track(void)
{
  return;
}

int COMMENT_STRING_LENGTH;
char COMMENT_STRING_FIRST_CHAR;
char COMMENT_STRING_SECOND_CHAR;

void init_global_variables(void){
  COMMENT_STRING_LENGTH = 1;
  COMMENT_STRING_FIRST_CHAR = '#';
  COMMENT_STRING_SECOND_CHAR = ';';
}
