FLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

LIBS_O = io_status.o io_array.o m_func.o m_sort.o

LIBS_H = io_status.h io_array.h m_func.h m_sort.h

VG = -O0 -g

all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out
	rm -f *.o

zip:
	zip Vakhrushev_NR.zip *.c *.h Makefile

clean:
	rm -f *.o *.out

%.o: %.c
	gcc -c $(FLAGS) $<

%.out: %.o
	gcc $(FLAGS) $^ -o $@

io_array.o: io_array.c io_array.h io_status.h
io_status.o: io_status.c io_status.h
m_func.o: m_func.c m_func.h
m_sort.o: m_sort.c m_sort.h io_array.h

a01.out: a01.o $(LIBS_O)
a01.o: a01.c $(LIBS_H)

a02.out: a02.o $(LIBS_O)
a02.o: a02.c $(LIBS_H)

a03.out: a03.o $(LIBS_O)
a03.o: a03.c $(LIBS_H)

a04.out: a04.o $(LIBS_O)
a04.o: a04.c $(LIBS_H)

a05.out: a05.o $(LIBS_O)
a05.o: a05.c $(LIBS_H)

a06.out: a06.o $(LIBS_O)
a06.o: a06.c $(LIBS_H)

a07.out: a07.o $(LIBS_O)
a07.o: a07.c $(LIBS_H)

a08.out: a08.o $(LIBS_O)
a08.o: a08.c $(LIBS_H)

a09.out: a09.o $(LIBS_O)
a09.o: a09.c $(LIBS_H)

a10.out: a10.o $(LIBS_O)
a10.o: a10.c $(LIBS_H)
