OPTS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

VG = -O0 -g

all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out
	rm -f *.o

zip:
	zip Vakhrushev_NR.zip *.c *.h Makefile

clean:
	rm -f *.o *.out

m_func.o: m_func.c m_func.h
	gcc -c $(OPTS) m_func.c

io_status.o: io_status.c io_status.h
	gcc -c $(OPTS) io_status.c

io_array.o: io_array.c io_array.h io_status.h
	gcc -c $(OPTS) io_array.c

t01_main.o: t01_main.c io_array.h io_status.h
	gcc -c $(OPTS) t01_main.c

a01.out: t01_main.o io_array.o io_status.o m_func.o
	gcc $(OPTS) t01_main.o io_array.o io_status.o m_func.o -o a01.out

t02_main.o: t02_main.c io_array.h io_status.h
	gcc -c $(OPTS) t02_main.c

a02.out: t02_main.o io_array.o io_status.o m_func.o
	gcc $(OPTS) t02_main.o io_array.o io_status.o m_func.o -o a02.out

t03_main.o: t03_main.c io_array.h io_status.h
	gcc -c $(OPTS) t03_main.c

a03.out: t03_main.o io_array.o io_status.o m_func.o
	gcc $(OPTS) t03_main.o io_array.o io_status.o m_func.o -o a03.out

t04_main.o: t04_main.c io_array.h io_status.h
	gcc -c $(OPTS) t04_main.c

a04.out: t04_main.o io_array.o io_status.o m_func.o
	gcc $(OPTS) t04_main.o io_array.o io_status.o m_func.o -o a04.out

t05_main.o: t05_main.c io_array.h io_status.h
	gcc -c $(OPTS) t05_main.c

a05.out: t05_main.o io_array.o io_status.o m_func.o
	gcc $(OPTS) t05_main.o io_array.o io_status.o m_func.o -o a05.out

t06_main.o: t06_main.c io_array.h io_status.h
	gcc -c $(OPTS) t06_main.c

a06.out: t06_main.o io_array.o io_status.o m_func.o
	gcc $(OPTS) t06_main.o io_array.o io_status.o m_func.o -o a06.out

t07_main.o: t07_main.c io_array.h io_status.h
	gcc -c $(OPTS) t07_main.c

a07.out: t07_main.o io_array.o io_status.o m_func.o
	gcc $(OPTS) t07_main.o io_array.o io_status.o m_func.o -o a07.out

t08_main.o: t08_main.c io_array.h io_status.h
	gcc -c $(OPTS) t08_main.c

a08.out: t08_main.o io_array.o io_status.o m_func.o
	gcc $(OPTS) t08_main.o io_array.o io_status.o m_func.o -o a08.out
