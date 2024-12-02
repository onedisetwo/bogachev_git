FLAGS1 =  -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -Wuninitialized
FLAGS2 = -O3
#FLAGS2 = -g

LIBS_H = errors.h matrix_io.h matrix.h solve.h main.h
LIBS_O = errors.o matrix_io.o matrix.o solve.o main.o

all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out a11.out

clean:
	rm -f *.o *.out

zip:
	zip Vakhrushev_NR.zip *.c *.h Makefile

%.o: %.c $(LIBS_H)
	gcc -c $(FLAGS1)  $(FLAGS2)  $<

%.out: %.o $(LIBS_O)
	gcc $(FLAGS1)  $(FLAGS2)  $^  -o $@
