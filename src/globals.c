#include "globals.h"
#include "utils.h"

struct config CF;
struct config *PTCF = &CF;

void debug_track(void)
{
  return;
}

void init_global_variables(void){
  PTCF->COMMENT_STRING_LENGTH = 1;
  PTCF->COMMENT_STRING_FIRST_CHAR = '#';
  PTCF->COMMENT_STRING_SECOND_CHAR = ';';
}
