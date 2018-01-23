OBJS4= sig.o

SRC = $(OBJS:.o=.cc)


# Compiler settings
CC              = g++
CFLAGS          = -std=c++11
INCLUDES        = -Iincludes


.PHONY: clean all

all: $(OBJS4)

sig: $(OBJS4)
	$(CC) $(CFLAGS)  -o $@ $(OBJS4)
sig.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c -o sig.o sig_selec.cc 

clean:
	rm build/*
