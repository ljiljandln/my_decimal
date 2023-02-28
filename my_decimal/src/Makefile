CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -std=c11 -pedantic -g
GCOV_FLAGS		= -fprofile-arcs -ftest-coverage -fPIC
VALGRIND_FLAGS	= --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med #--track-fds=yes --show-leak-kinds=all
CHECK_FLAGS 	= $(shell pkg-config --cflags --libs check)

LIBRARY			= s21_decimal.a
SRC_PROJECT		= $(wildcard converters/*.c arithmetic/*.c rounding/*.c comparison/*.c core/*.c)
SRC_TEST		= tests/test_arithmetic.c tests/test_comparison.c tests/test_converters.c tests/test_rounding.c
OBJ_PROJECT		= s21_arithmetic.o s21_comparison.o s21_converters.o s21_rounding.o s21_core.o s21_big_decimal.o
OBJ_TEST		= test_arithmetic.o test_comparison.o test_converters.o test_rounding.o test_core.o


all: rebuild gcov_report

$(LIBRARY): $(SRC_PROJECT)
	$(CC) $(CFLAGS) -c $(SRC_PROJECT)
	ar rc $(LIBRARY) $(OBJ_PROJECT)
	ranlib $(LIBRARY)

test: $(LIBRARY) $(OBJ_TEST)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(OBJ_TEST) -o test $(LIBRARY) $(CHECK_FLAGS)
	./test

gcov_report: clean $(OBJ_TEST)
	$(CC) $(CFLAGS) -o test $(OBJ_TEST) --coverage $(SRC_PROJECT) $(CHECK_FLAGS)
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	make open

test_arithmetic.o:
	$(CC) -c tests/test_arithmetic.c

test_comparison.o:
	$(CC) -c tests/test_comparison.c

test_converters.o:
	$(CC) -c tests/test_converters.c

test_rounding.o:
	$(CC) -c tests/test_rounding.c

test_core.o:
	$(CC) $(CFLAGS) -c tests/test_core.c

clean:
	rm -rf test
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcda
	rm -rf report
	rm -rf *.gcno
	rm -rf *.info
	rm -rf valgrind.txt

rebuild: clean test

open: 
	open report/index.html

.PHONY: all clean rebuild open clang valgrind docker

valgrind: rebuild
	valgrind $(VALGRIND_FLAGS) ./test
	grep -n "ERROR SUMMARY" valgrind.txt #| grep -v "0 errors"

clang:
	clang-format --style=google -i arithmetic/*
	clang-format --style=google -i comparison/*
	clang-format --style=google -i converters/*
	clang-format --style=google -i core/*
	clang-format --style=google -i rounding/*
	clang-format --style=google -i tests/*

docker:
	cd ../materials/build; sudo sh run.sh; cd ../../src
