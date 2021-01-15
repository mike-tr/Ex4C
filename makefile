# $@ the current target file
# $^ all sources listed for the current target
# $< the first (left-most) source for the current 

FLAGS = -Wall -g
CC = gcc
AR = ar

TARGET_INPUT = input.txt

PROGRAM = frequency
MYOBJECTS = reader.o trie.o

run_v: $(PROGRAM)
	valgrind ./$< < $(TARGET_INPUT)

run_r: $(PROGRAM)
	./$< r < $(TARGET_INPUT)

run: $(PROGRAM)
	./$< < $(TARGET_INPUT)

run_s: $(PROGRAM)
	./$< < $(TARGET_INPUT)

all: $(PROGRAM) 
$(PROGRAM) : $(PROGRAM).o $(MYOBJECTS)
	gcc $(FLAGS) -o $@ $^

$(PROGRAM).o : $(PROGRAM).c
	gcc $(FLAGS) -c $<

%.o : %.c reader.h trie.h
	gcc $(FLAGS) -c $< > out.txt

PHONY: run_s, run_f, clean, all

clean:
	rm -f *.o *.a *.so $(PROGRAM) *.exe

delo:
	rm -f *.o *.exe