CC = gcc -Wall -Werror -Wextra -std=c11

s21_cat: 
	$(CC) s21_cat.c s21_cat.h -o $@

tests: s21_cat
	sh test_cat.sh

clean:
	rm s21_cat log.txt

rebuild: clean s21_cat

all: s21_cat tests clean