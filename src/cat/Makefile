CC := gcc
CCFLAGS := -Wall -Werror -Wextra -std=c11

all: clang_format s21_cat

s21_cat:
	$(CC) $(CCFLAGS) -o s21_cat *.c

cat_test: s21_cat
	bash cat_test.sh

clang_format:
	clang-format -style=Google -i ./*.h ./*.c

clean:
	rm s21_cat

rebuild: clean all

