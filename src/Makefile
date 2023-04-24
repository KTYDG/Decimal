CC= gcc
CFLAG= -Wall -Werror -Wextra -std=c11 # -g # 
CHECKFLAG= -lcheck
ifeq ($(shell uname),Linux)
		CHECKFLAG+= -lsubunit -lrt -lm -lpthread
endif

all: s21_decimal.a

rebuild: clean s21_decimal.a

s21_decimal.a: s21_arith.o s21_comp.o s21_conv.o s21_over.o s21_common.o s21_big_decimal.o
	ar rcs $@ $^
	rm -rf $^

gcov_report: test_gcov
	lcov -c -d ./ -o s21_test.info
	genhtml -o ./report s21_test.info
	open ./report/index.html
	rm -rf *.gcda *gcno s21_test.info *.dSYM

clean:
	rm -rf *.o *.a report *.gcno *.gcda *.info *.dSYM report || true

clang:
	# clang-format -style=google -dump-config > .clang-format
	cp ../materials/linters/.clang-format ./
	clang-format -n -style=file *.[ch]
	clang-format -n -style=file */*.[ch]
	rm -rf .clang-format


# anna: rebuild
# 	$(CC) -Wall anna.c s21_decimal.a -lm -o $@
# 	./$@
# 	rm -rf anna


s21_arith.o: s21_arith.c
	$(CC) $(CFLAG)$(COVER) -c $^ -o $@

s21_comp.o: s21_comp.c
	$(CC) $(CFLAG)$(COVER) -c $^ -o $@

s21_conv.o: s21_conv.c
	$(CC) $(CFLAG)$(COVER) -c $^ -o $@

s21_over.o: s21_over.c
	$(CC) $(CFLAG)$(COVER) -c $^ -o $@

s21_common.o: s21_common.c
	$(CC) $(CFLAG)$(COVER) -c $^ -o $@

s21_big_decimal.o: s21_big_decimal.c
	$(CC) $(CFLAG)$(COVER) -c $^ -o $@


test_arithmetic:
	$(CC) $(CFLAG)$(COVER) tests/test_arithmetic.c s21_decimal.a $(CHECKFLAG) -o $@
	./$@ || true
	rm -rf $@

test_comparison:
	$(CC) $(CFLAG)$(COVER) tests/test_comparison.c s21_decimal.a $(CHECKFLAG) -o $@
	./$@ || true
	rm -rf $@

test_f_to_d:
	$(CC) $(CFLAG)$(COVER) tests/test_f_to_d.c s21_decimal.a $(CHECKFLAG) -o $@
	./$@ || true
	rm -rf $@

test_d_to_f:
	$(CC) $(CFLAG)$(COVER) tests/test_d_to_f.c s21_decimal.a $(CHECKFLAG) -o $@
	./$@ || true
	rm -rf $@

test_d_to_i:
	$(CC) $(CFLAG)$(COVER) tests/test_d_to_i.c s21_decimal.a $(CHECKFLAG) -o $@
	./$@ || true
	rm -rf $@

test_i_to_d:
	$(CC) $(CFLAG)$(COVER) tests/test_i_to_d.c s21_decimal.a $(CHECKFLAG) -o $@
	./$@ || true
	rm -rf $@

test_floor:
	$(CC) $(CFLAG)$(COVER) tests/test_floor.c s21_decimal.a $(CHECKFLAG) -o $@
	./$@ || true
	rm -rf $@

test_round:
	$(CC) $(CFLAG)$(COVER) tests/test_round.c s21_decimal.a $(CHECKFLAG) -o $@
	./$@ || true
	rm -rf $@

test_truncate:
	$(CC) $(CFLAG)$(COVER) tests/test_truncate.c s21_decimal.a $(CHECKFLAG) -o $@
	./$@ || true
	rm -rf $@

test_negate:
	$(CC) $(CFLAG)$(COVER) tests/test_negate.c s21_decimal.a $(CHECKFLAG) -o $@
	./$@ || true
	rm -rf $@

test: rebuild test_comparison test_arithmetic test_f_to_d test_d_to_f test_d_to_i test_i_to_d test_floor test_round test_truncate test_negate
	rm -rf *.dSYM

test_gcov: coverlib covertest

coverlib: COVER= -fprofile-arcs -ftest-coverage
coverlib: rebuild
covertest: COVER= -fprofile-arcs
covertest: test_comparison test_arithmetic test_f_to_d test_d_to_f test_d_to_i test_i_to_d test_floor test_round test_truncate test_negate
