FLAGS1 = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
FLAGS2 = -O3
#FLAGS2 = -g

LIBS_H = errors.h solve.h
LIBS_O = errors.o solve.o

all: a01.out a02.out a03.out a04.out a05.out

clean:
	rm -f *.o *.out

zip:
	zip Vakhrushev_NR.zip *.c *.h Makefile

%.o: %.c $(LIBS_H)
	gcc -c $(FLAGS1) $(FLAGS2) $<

%.out: %.o $(LIBS_O)
	gcc $(FLAGS1) $(FLAGS2) $^ -o $@
