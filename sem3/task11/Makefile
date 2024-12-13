FLAGS1 = -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
FLAGS2 = -O3

LIBS_H = io_status.h student.h b_tree.h
LIBS_O = io_status.o b_tree.o #student.o

all: a.out

clear:
	rm -f *.o *.out

zip:
	zip Vakhrushev_NR.zip *.cpp *.h Makefile

%.o: %.cpp $(LIBS_H)
	g++ -c $(FLAGS1)  $(FLAGS2)  -lm  $<

%.out: %.o $(LIBS_O)
	g++ $(FLAGS1)  $(FLAGS2)  $^  -lm  -o $@
