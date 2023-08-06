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
  strbuf_delete_between(list[0], list[2]);

  print_strbuf_list(*list);
}

int main(int argc, char * argv[])
{
  // test();
  if (argc <= 1){
    printf("%s\n", "No argument given!");
    return 0;
  }

  struct strbuf *sbp;
  strbuf_init(&sbp);          

  read_to_strbuf(sbp, argv[1]);
  format_strbuf_list(&sbp);             

  print_strbuf_list(sbp);  
  debug_print(sbp);

  return 0;
}
