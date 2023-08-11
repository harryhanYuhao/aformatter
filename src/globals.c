#include "globals.h"
#include "utils.h"

struct config CF;
struct config *PTCF = &CF;

// This strbuf is a linked-list for the filenames that needs to be formatted.
struct strbuf *FILENAMES;

void init_global_variables(void){
  strbuf_init(&FILENAMES);
  PTCF->COMMENT_STRING_LENGTH = 1;
  PTCF->COMMENT_STRING_FIRST_CHAR = '#';
  PTCF->COMMENT_STRING_SECOND_CHAR = ';';
}
