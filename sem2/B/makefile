FLAG = -c -O3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs

all: a.out

a.out: task03.o array_io.o double_comparison.o initial.o help_funcs.o norm.o
	gcc $^ -o $@

%.o: %.c
	gcc $(FLAG) $^ -o $@

clean:
	rm -f *.o *.out all