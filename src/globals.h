#ifndef GLOBALS_H
#define GLOBALS_H 1

struct config {
  int COMMENT_STRING_LENGTH;
  char COMMENT_STRING_FIRST_CHAR;
  char COMMENT_STRING_SECOND_CHAR;
};

extern struct config CF; // config
extern struct config *PTCF;  // pointer to config

void debug_track(void);
void init_global_variables(void);

#endif // for GLOBALS_H
