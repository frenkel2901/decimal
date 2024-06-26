OS = $(shell uname)
ifeq ("$(OS)","Linux")
	LEAKS_RUN_TEST = valgrind --tool=memcheck --leak-check=yes --log-file="valgrind_test.txt" ./test 
else
	LEAKS_RUN_TEST = leaks -atExit-- ./test
endif

CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -pedantic
CFLAGS_TEST = -std=c11 -Wall -Werror -Wextra -pedantic 
GCOVFLAGS = --coverage
GCOV = gcovr 

CLANG_FORMAT = ../materials/linters/.clang-format

ifeq ($(shell uname -p), arm)
	CC = gcc-14 
	GCOV = gcov-14
endif

SRC=s21_sub.c s21_mul.c s21_div.c s21_extra_func.c s21_from_decimal_to_float.c s21_from_decimal_to_int.c $\
s21_from_float_to_decimal.c s21_from_int_to_decimal.c s21_is_equal.c s21_is_greater_or_equal.c s21_is_greater.c $\
s21_is_less_or_equal.c s21_is_less.c s21_is_not_equal.c s21_negate.c s21_round.c s21_floor.c s21_truncate.c s21_add.c

OBJECTS = $(addprefix obj/,$(SRC:.c=.o))
OBJECTS_GCOV = $(addprefix gcov_obj/,$(SRC:.c=.o))

CHECK_FILE = ./tests/*.check

FREE_TEST = rm -rf test.c test.o

all: s21_decimal.a
	
clean:
	rm -rf *.o *.so *.a *.out *.gcda *.gcno *.info test test.c test_gcov report obj gcov_obj

rebuild: clean all

s21_decimal.a: $(OBJECTS) s21_decimal.h s21_extra_func.h
	ar rc s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a

s21_decimal_gcov.a: $(OBJECTS_GCOV)
	ar rc s21_decimal_gcov.a $(OBJECTS_GCOV)
	ranlib s21_decimal_gcov.a

test.c:
	checkmk clean_mode=1 $(CHECK_FILE) > test.c	

test.o: test.c s21_decimal.h
	$(CC) $(CFLAGS_TEST) -g -c test.c	

test: clean test.o s21_decimal.a	
	$(CC) $(CFLAGS) -g test.o -o test `pkg-config --cflags --libs check` -L. s21_decimal.a -lm
	./test
	$(FREE_TEST)

leak_test: clean test.o s21_decimal.a
	$(CC) $(CFLAGS) -g test.o -o test `pkg-config --cflags --libs check` -L. s21_decimal.a -lm
	$(LEAKS_RUN_TEST)
	$(FREE_TEST)	

gcov_report: clean test.o s21_decimal_gcov.a
	$(CC) $(CFLAGS) test.o -o gcov_obj/test_gcov `pkg-config --cflags --libs check` -L. s21_decimal_gcov.a $(GCOVFLAGS) -lm
	gcov_obj/test_gcov
	mkdir -p report
	$(GCOV) --html-details report/index.html --html-medium-threshold 80 --html-high-threshold 100 --html-title "Coverage s21_decimal report"
	$(FREE_TEST)

obj/%.o: %.c
	mkdir -p obj/
	$(CC) $(CFLAGS) -g -c $< -o $@

gcov_obj/%.o: %.c
	mkdir -p gcov_obj
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

clang:
	clang-format --style=file:$(CLANG_FORMAT) -i *.c *.h
	clang-format --style=file:$(CLANG_FORMAT) -n *.c *.h

check:
	cppcheck -q --enable=warning,portability --inconclusive ./

.PHONY: all clean rebuild clang check

gcov_mac: clean test.o s21_decimal_gcov.a
	$(CC) $(CFLAGS) test.o -o gcov_obj/test_gcov `pkg-config --cflags --libs check` -L. s21_decimal_gcov.a $(GCOVFLAGS) -lm
	gcov_obj/test_gcov
	mkdir -p report
	lcov -t "Report" -c -d ./gcov_obj --output-file ./report/coverage.info --gcov-tool $(GCOV) --rc branch_coverage=1
	genhtml ./report/coverage.info --output-directory ./report/ --rc branch_coverage=1