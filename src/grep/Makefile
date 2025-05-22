GCC := gcc
CCFLAGS := -Wall -Werror -Wextra -std=c11

all: clang_format s21_grep

s21_grep:
	$(CC) $(CCFLAGS) -o $@ ./*.c

grep_test: s21_grep
	bash grep_test.sh

grep_valgrind: 
	CK_FORK=no valgrind -s  --track-origins=yes --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=RESULT_VALGRIND.txt ./grep_test.sh

clang_format:
	clang-format -style=Google -i ./*.h ./*.c

clean:
	rm s21_grep

rebuild: clean s21_grep