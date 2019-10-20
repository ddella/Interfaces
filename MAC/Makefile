# Makefile
# note the -c option, which means: "compile, but don't link"
# $< will expand to the first source file
# $^ will expand to all source files

CC = gcc
CXXFLAGS = -Wall

all: myprog

object: get_if_mac.c get_if_mac.h
	$(CC) $(CXXFLAGS) -c $<

myprog: get_if_mac.c myprog.c
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o myprog
