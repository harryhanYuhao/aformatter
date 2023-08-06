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

  print_strbuf_list(*list, STDOUT_FILENO);  // 1 is stdout
}

void init(void)
{
  init_global_variables();
}

void create_backup(char *name, struct strbuf *sbptr)
{
  int fd = open(name, O_TRUNC|O_RDWR|O_CREAT, 00666);

  struct strbuf *cur = sbptr;
  while (1){
    if (cur->sptr!=NULL){
      // syscall, requires unistd.h
      write(fd, cur->sptr, cur->len);
    }
    if (cur->next==NULL)
      break;
    cur=cur->next;
  }

  if (close(fd)==-1){
    char errorString[64]; 
    snprintf(errorString, 64, "fail to open file %s", name);
    exit_program(errorString, -1);
  }
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
  
  char *bkname = (char *) calloc(strlen(argv[1]+4), 1);
  sprintf(bkname, "%s.bak", argv[1]);
  printf("%s\n", bkname);

  create_backup(bkname, sbp);

  format_strbuf_list(&sbp);             

  // overwrite original file
  int fd = open(argv[1], O_TRUNC|O_RDWR);
  print_strbuf_list(sbp, fd);  
  if (close(fd)==-1){
    char errorString[64]; 
    snprintf(errorString, 64, "fail to open file %s", argv[1]);
    exit_program(errorString, -1);
  }

  // print to stdout
  print_strbuf_list(sbp, STDOUT_FILENO); 
  
  printf(
    "%sNOTE:%sThe preceding lines overwrite the file %s; "
    "the back up of it was created as %s%s%s.\n",
    "\x1b[31;1m","\x1b[0m",argv[1], "\x1b[3m",bkname,"\x1b[0m");
  
  // debug_print(sbp);

  return 0;
}
