#include "utils.h"
#include "globals.h"
// remove all spaces in a line if this line consist of only spaces
// the line is retained 
void strip_trailing_space(struct strbuf * sbptr)
{
  struct strbuf *cur = sbptr;
  struct strbuf *poke = sbptr;

  for (;cur->next != NULL; cur = cur->next){
    poke = cur->next;
    while (strbuf_is_space(poke)){
      poke = poke->next;
    }
    if (strbuf_is_linebreak(poke))
      strbuf_delete_between(cur, poke);
  }
}

void strip_initial_space(struct strbuf * sbptr)
{
  struct strbuf *cur = sbptr;
  struct strbuf *poke = sbptr;
  //
  // first take care of the space at the beginning of the document
  while (strbuf_is_space(cur)){
    // self delete make cur equal to that of cur->next
    strbuf_self_delete(cur);
  }

  for (;cur->next != NULL; cur = cur->next){
    if (!strbuf_is_linebreak(cur))
      continue;
    poke = cur->next;
    while (strbuf_is_space(poke)){
      poke = poke->next;
    }
    strbuf_delete_between(cur, poke);
  }
}

// remove extra line breaks if there is three or more consecutive line breaks
// reduce number of consecutive linebreaks to two
void strip_repetitive_linebreaks(struct strbuf * sbptr)
{
  struct strbuf * cur = sbptr;
  while (1){
    if (strbuf_is_linebreak(cur)){
      while 
        (strbuf_is_linebreak(cur->next) && strbuf_is_linebreak(cur->next->next))
        strbuf_remove_next(cur);
    }
    if (cur->next==NULL)
      break;
    // to avoid segfault:
    // can not be written as if(cur->next == NULL || cur->next->next==NULL)
    if (cur->next->next==NULL)
      break;
    cur = cur->next;
  }
}

/// assigne token code for each strbuf .
void strbuf_tokenisation(struct strbuf *sbptr)
{
  struct strbuf *cur = sbptr;
  int tmp;
  while (cur->next!=NULL){
    if (strbuf_is_null_strbuf(cur)){
      strbuf_self_delete(cur);
    }
      // note strbuf_is_comment return 0 if it is not comment 
      // it return a positive int if it is comment, 
      // the int tells how long the comment is (in terms of tokens)
      // tmp = the number of tokens the comments consists of, not including
      // the comment sign
    else if ((tmp = strbuf_is_comment(cur))){
      cur->token = 0; 
      for (int i = 0; i < tmp-1; i++){
        strbuf_merge(cur, cur->next);
      }
    }
    else if (strbuf_is_section(cur)){
      cur->token = 1;
    }
    else if (strbuf_is_label(cur)){
      cur->token = 3;
    }
    else if (strbuf_is_space(cur)){
      // cur->token = 32;
      // when it deletes itself it become the next token: need not cur = cur->next
      strbuf_self_delete(cur);
      continue;
    } else if (strbuf_is_linebreak(cur)){
      cur->token = 10;
    } else if (cur->token == -1){
      cur -> token = 2;
    }
    cur=cur->next;
  }
}

// the struct strbuf * inserted here shall be the initial 
//struct strbuf * of the linked list and being cleaned up and tokenised
void format_insert_spaces(struct strbuf *sbptr)
{
  struct strbuf *cur = sbptr;
  while(cur->next != NULL){
    if (cur->token == 1){
      strbuf_presert_n_spaces_before(cur, 4);
      cur = cur->next;
    }
    cur = cur->next;
  }
}
