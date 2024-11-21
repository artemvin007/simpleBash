#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct flags {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
  bool err;
};

void solo_flags_enabler(char* flag_str, struct flags* f);
void flag_enabler(char* flag_str, struct flags* f);
void print_char(int c, struct flags* f, int* prev_c, bool* back_n_was_write,
                int* str_counter);
void print_file(char* filename, struct flags* f);
void args_processing(char* arg, struct flags* f);

#endif