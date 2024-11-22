CC = gcc -Wall -Werror -Wextra -std=c11

s21_grep: 
	$(CC) s21_grep.c s21_grep.h -o $@

tests: s21_grep
	echo "--------func test--------"
	sh test_grep/test_func_grep.sh
	echo "--------leak test--------"
	sh test_grep/test_leak_grep.sh

clean:
	rm s21_grep

rebuild: clean s21_grep
