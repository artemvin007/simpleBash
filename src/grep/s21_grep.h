#ifndef GREP_S21
#define GREP_S21

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  int f_c;
  bool err;
};

char* read_str(FILE* fp);
void to_lower(char* s);
char* str_copy(char* s);
void flag_enabler(struct flags* f, char* flags_str, char** template);
bool search(struct flags* f, char* s, char* template);
void str_print(struct flags* f, char* s, char* filename, int* str_counter);
int str_processing(char* filename, struct flags* f, char* s, char* template,
                   int* str_counter);
void file_processing(char* filename, struct flags* f, char* template);
void args_processing(char* arg, struct flags* f, char** template);

#endif