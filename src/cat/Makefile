CC = gcc -Wall -Werror -Wextra -std=c11

s21_cat: 
	$(CC) s21_cat.c s21_cat.h -o $@

tests: s21_cat
	echo "-------func test--------"
	sh test_cat/test_func_cat.sh
	echo "-------leak test--------"
	sh test_cat/test_leak_cat.sh

clean:
	rm s21_cat 

rebuild: clean s21_cat

all: s21_cat tests clean