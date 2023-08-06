#include <fcntl.h>  // for open() syscall
#include <stdio.h>  // for printf
#include <errno.h>  // for errno

#include "utils.h"
#include "globals.h"
#include "parse.h"


void format_strbuf_list(struct strbuf **sbpp)
{
  struct strbuf * sbp = *sbpp;
  strip_initial_space(sbp);
  strip_trailing_space(sbp);
  strip_repetitive_linebreaks(sbp);
  
  strbuf_tokenisation(sbp);
  format_insert_spaces(sbp);
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
  // strbuf_delete_between(list[0], list[2]);
  strbuf_presert_before(*list, global_tab);

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

  struct strbuf *sbp;
  strbuf_init(&sbp);          

  read_to_strbuf(sbp, argv[1]);
  for (int i = 0; i < 11; i++){
    strbuf_self_delete(sbp);
  }
  format_strbuf_list(&sbp);             

  print_strbuf_list(sbp);  
  debug_print(sbp);

  debug_track();

  return 0;
}
