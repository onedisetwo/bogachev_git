FLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

LIBS_H = m_string.h test.h
LIBS_O = m_string.o test.o

all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out

clean:
	rm -f *.o *.out

zip:
	zip Vakhrushev_NR.zip *.c *.h Makefile

%.o: %.c
	gcc -c $(FLAGS) $<

%.out: %.o
	gcc $(FLAGS) $^ -o $@

m_string.o: m_string.c m_string.h
test.o: test.c test.h

a01.o: a01.c $(LIBS_H)
a01.out: a01.o $(LIBS_O)

a02.o: a02.c $(LIBS_H)
a02.out: a02.o $(LIBS_O)

a03.o: a03.c $(LIBS_H)
a03.out: a03.o $(LIBS_O)

a04.o: a04.c $(LIBS_H)
a04.out: a04.o $(LIBS_O)

a05.o: a05.c $(LIBS_H)
a05.out: a05.o $(LIBS_O)

a06.o: a06.c $(LIBS_H)
a06.out: a06.o $(LIBS_O)

a07.o: a07.c $(LIBS_H)
a07.out: a07.o $(LIBS_O)

a08.o: a08.c $(LIBS_H)
a08.out: a08.o $(LIBS_O)

a09.o: a09.c $(LIBS_H)
a09.out: a09.o $(LIBS_O)

a10.o: a10.c $(LIBS_H)
a10.out: a10.o $(LIBS_O)
