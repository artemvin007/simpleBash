#include "s21_cat.h"

void solo_flags_enabler(char* flag_str, struct flags* f) {
  switch (flag_str[0]) {
    case 'b':
      f->b = true;
      break;
    case 'e':
      f->e = true;
      f->v = true;
      break;
    case 'n':
      f->n = true;
      break;
    case 's':
      f->s = true;
      break;
    case 't':
      f->t = true;
      f->v = true;
      break;
    case 'v':
      f->v = true;
      break;
    case 'E':
      f->e = true;
      break;
    case 'T':
      f->t = true;
      break;
    default:
      f->err = true;
      break;
  }
}

void flag_enabler(char* flag_str, struct flags* f) {
  if (strcmp("--number-nonblank", flag_str) == 0) {
    f->b = true;
  } else if (strcmp("--number", flag_str) == 0) {
    f->n = true;
  } else if (strcmp("--squeeze-blank", flag_str) == 0) {
    f->s = true;
  } else {
    for (size_t flagi = 1; flagi < strlen(flag_str); flagi++) {
      solo_flags_enabler(flag_str + flagi, f);
    }
  }
}

void print_char(int c, struct flags* f, int* prev_c, bool* back_n_was_write,
                int* str_counter) {
  bool need_to_write = true;
  if (f->s && *prev_c == '\n' && c == '\n') {
    if (*back_n_was_write) {
      need_to_write = false;
    } else {
      *back_n_was_write = true;
    }
  }
  if (f->n && *prev_c == '\n' && need_to_write) {
    printf("%6d	", *str_counter);
    *(str_counter) += 1;
  }
  if (f->b && *prev_c == '\n' && c != '\n') {
    printf("%6d	", *str_counter);
    *(str_counter) += 1;
  }
  if (f->t && c == 9) {
    printf("^I");
    need_to_write = false;
  }
  if (f->v && c != '\n' && c != '\t' && c < 32) {
    printf("^");
    c += 64;
  } else if (c == 127) {
    printf("^");
    c = '?';
  }

  if (need_to_write) {
    if (f->e && c == '\n') {
      printf("$");
    }

    printf("%c", c);
    if (c != '\n') {
      *back_n_was_write = false;
    }
  }
}

void print_file(char* filename, struct flags* f) {
  FILE* fp;
  int str_counter = 1;
  if ((fp = fopen(filename, "r")) != NULL) {
    int prev_c = '\n';
    int c = fgetc(fp);

    bool back_n_was_write = false;
    if (f->b) {
      f->n = false;
    }
    while (c != EOF) {
      print_char(c, f, &prev_c, &back_n_was_write, &str_counter);
      prev_c = c;
      c = fgetc(fp);
    }

    fclose(fp);
  } else {
    printf("No such file %s\n", filename);
  }
}

void args_processing(char* arg, struct flags* f) {
  if (arg[0] == '-') {
    flag_enabler(arg, f);
  } else if (f->err == false) {
    print_file(arg, f);
  } else {
    printf("Wrong flag\n");
  }
}

int main(int argc, char* argv[]) {
  if (argc > 1) {
    struct flags f = {false, false, false, false, false, false, false};
    for (int argi = 1; argi < argc; argi++) {
      args_processing(argv[argi], &f);
    }
  } else {
    printf("Input filename\n");
  }

  return (0);
}
