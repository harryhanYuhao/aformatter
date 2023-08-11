#include <fcntl.h>  // for open() syscall
#include <stdio.h>  // for printf
#include <errno.h>  // for errno

#include "utils.h"
#include "globals.h"
#include "parse.h"

 format_file(char *filename)
{
  struct strbuf *sbp;
  strbuf_init(&sbp);          
  read_to_strbuf(sbp, filename);

  strip_initial_space(sbp);
  strip_trailing_space(sbp);
  strip_repetitive_linebreaks(sbp);
  
  strbuf_tokenisation(sbp);
  delete_tobe_deleted(sbp);
  format_insert_spaces(sbp);

  /* create formatted file */
  char *bkname = (char *) calloc(strlen(filename)+10, 1);
  sprintf(bkname, "formatted_%s", filename);
  save_to_file(bkname, sbp);

  // print to stdout
  print_strbuf_list(sbp);
  strbuf_free_list(sbp);

  // debug_print(sbp);
}

// create a linked-list with size of ten
// each holding different ascii character
void test(void){
  struct strbuf **list = (struct strbuf **) calloc(10, sizeof(struct strbuf**));
  for (int i = 0; i < 10; i++){
    struct strbuf *tmp;
    strbuf_init(&tmp);
    list[i] = tmp;
  }
  for (int i = 0; i < 9; i++){
    list[i]->next = list[i+1];
  }
  for (int i = 0; i < 10; i++){
    char tmp = 40+i;
    strbuf_append(list[i], &tmp, 1);
  }

  print_strbuf_list(*list);
}

void init(void)
{
  init_global_variables();
}

int main(int argc, char * argv[])
{
  init();
  // test();
  if (argc <= 1){
    printf("%s\n", "No argument given!");
    return 0;
  }

  format_file(argv[1]);             

  // printf(
  //   "%sNOTE:%sThe preceding lines overwrite the file %s; "
  //   "the back up of it was created as %s%s%s.\n",
  //   "\x1b[31;1m","\x1b[0m",argv[1], "\x1b[3m",bkname,"\x1b[0m");
  
  return 0;
}
