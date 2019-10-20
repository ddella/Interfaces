# Makefile
# note the -c option, which means: "compile, but don't link"
# $< will expand to the first source file
# $^ will expand to all source files

CC = gcc
CXXFLAGS = -Wall

all: myprog

myprog: get_if_mac.o myprog.c
	$(CC) $(CXXFLAGS) -o $@ $^

get_if_mac.o: get_if_mac.c get_if_mac.h
	$(CC) $(CXXFLAGS) -c $<

clean:
	rm -f *.o myprog
