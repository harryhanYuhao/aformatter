#include "flags.h"

// all input are directed here, 
// the appropriate global varialbe are then setted
void process_input(int argc, char *argv[])
{
  struct strbuf *cur = FILENAMES;
  for (int i = 1; i < argc; i++){
    if (determine_flag_type(argv[i]) == 3){
      struct strbuf *tmp;
      strbuf_init(&tmp);
      strbuf_append(tmp, argv[i], strlen(argv[i]));
      strbuf_insert_after(cur, tmp);
      cur = cur->next;
    }
  }
  int counter = strip_null_strbuf(FILENAMES);
}
