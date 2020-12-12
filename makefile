## makefile for edge_runner

.PHONY: clean

RM = rm -f

test: edge_runner.o play.o startwin.o help.o map.o gameover.o
	gcc -o test edge_runner.o play.o startwin.o help.o map.o gameover.o -lcurses

edge_runner.o: edge_runner.c edge_runner.h
	gcc -Wall -g -c edge_runner.c -lcurses

play.o: play.c edge_runner.h
	gcc -Wall -g -c play.c -lcurses

startwin.o: startwin.c edge_runner.h
	gcc -Wall -g -c startwin.c -lcurses

help.o: help.c edge_runner.h
	gcc -Wall -g -c help.c -lcurses

map.o: map.c edge_runner.h
	gcc -Wall -g -c map.c -lcurses

gameover.o: gameover.c edge_runner.h
	gcc -Wall -g -c gameover.c -lcurses

clean:
	$(RM) *.o
