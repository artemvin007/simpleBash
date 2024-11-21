CC = gcc -Wall -Werror -Wextra -std=c11

s21_grep: 
	$(CC) s21_grep.c s21_grep.h -o $@

tests: s21_grep
	sh grep_test.sh

clean:
	rm s21_grep

rebuild: clean s21_grep
