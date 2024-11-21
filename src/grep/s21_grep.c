#include "s21_grep.h"

char* read_str(FILE* fp) {
  char* s = malloc(sizeof(char));
  int n = 1;
  s[n - 1] = fgetc(fp);
  while (s[n - 1] != EOF && s[n - 1] != '\n') {
    n++;
    s = realloc(s, n * sizeof(char));
    s[n - 1] = fgetc(fp);
  }
  n++;
  s = realloc(s, n * sizeof(char));
  s[n - 1] = '\0';
  return s;
}

void to_lower(char* s) {
  for (char* stri = s; *stri != '\0'; stri++) {
    if (*stri >= 'A' && *stri <= 'Z') {
      *stri = 'a' + *stri - 'A';
    }
  }
}

char* str_copy(char* s) {
  char* res = malloc(strlen(s) * sizeof(char));
  for (size_t i = 0; i < strlen(s); i++) {
    res[i] = s[i];
  }
  return res;
}

void flag_enabler(struct flags* f, char* flags_str, char** template) {
  for (char* flagi = flags_str; *flagi != '\0' && *template == NULL; flagi++) {
    if (f->e && *template == NULL) {
      *template = flagi;
    } else if (!f->e) {
      switch (*flagi) {
        case 'e':
          f->e = true;
          break;
        case 'i':
          f->i = true;
          break;
        case 'v':
          f->v = true;
          break;
        case 'l':
          f->l = true;
          break;
        case 'c':
          f->c = true;
          break;
        case 'n':
          f->n = true;
          break;
        default:
          f->err = true;
          break;
      }
    } else {
      f->err = true;
    }
  }
}

bool search(struct flags* f, char* s, char* template) {
  bool found = false;
  regex_t rx;
  int search_res = 0;
  if (f->i) {
    to_lower(template);
    char* s_copy = str_copy(s);
    to_lower(s_copy);
    search_res = regcomp(&rx, template, 0);
    search_res = regexec(&rx, s, 0, NULL, 0);
    free(s_copy);
  } else {
    search_res = regcomp(&rx, template, 0);
    search_res = regexec(&rx, s, 0, NULL, 0);
  }
  if (search_res == 0) {
    found = true;
  } else {
    found = false;
  }
  regfree(&rx);
  return (!found && f->v) || (found && !f->v);
}

void str_print(struct flags* f, char* s, char* filename, int* str_counter) {
  if (f->f_c > 1) {
    printf("%s:", filename);
  }
  if (f->n) {
    printf("%d:", *str_counter);
  }
  if (s[strlen(s) - 1] == EOF) {
    s[strlen(s) - 1] = '\n';
  }
  printf("%s", s);
}

int str_processing(char* filename, struct flags* f, char* s, char* template,
                   int* str_counter) {
  bool search_result = search(f, s, template);
  int res = 0;
  if (search_result) {
    res = 1;
    if (!f->l && !f->c) {
      str_print(f, s, filename, str_counter);
    }
  }
  return res;
}

void file_processing(char* filename, struct flags* f, char* template) {
  FILE* fp;
  if ((fp = fopen(filename, "r"))) {
    char* s = read_str(fp);
    int str_counter = 1;
    int match_counter = 0;
    while (s[0] != EOF) {
      match_counter += str_processing(filename, f, s, template, &str_counter);
      str_counter++;
      free(s);
      s = read_str(fp);
    }
    if (f->l && match_counter > 0) {
      match_counter = 1;
    }
    if (f->c) {
      if (f->f_c > 1) {
        printf("%s:", filename);
      }
      printf("%d\n", match_counter);
    }
    if (f->l && match_counter > 0) {
      printf("%s\n", filename);
    }
    free(s);
    fclose(fp);
  } else {
    printf("no such file\n");
  }
}

void args_processing(char* arg, struct flags* f, char** template) {
  if (arg[0] == '-' && !f->e) {
    flag_enabler(f, arg + 1, template);
  } else if (!f->err) {
    if (*template == NULL) {
      f->e = true;
      *template = arg;
      // printf("%s", *template);
    } else {
      file_processing(arg, f, *template);
    }
  } else {
    printf("wrong flags\n");
  }
}

int file_counter(int argc, char* argv[]) {
  int f_c = 0;
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-') {
      f_c++;
    }
  }
  f_c = argc - f_c - 2;
  return f_c;
}

int main(int argc, char* argv[]) {
  if (argc > 1) {
    char* template = NULL;
    struct flags f = {
        false, false, false, false, false, false, file_counter(argc, argv),
        false};
    for (int argi = 1; argi < argc && f.f_c > 0; argi++) {
      args_processing(argv[argi], &f, &template);
    }
    if (f.f_c <= 0) {
      printf("input some more\n");
    }
  } else {
    printf("input something\n");
  }
  return 0;
}