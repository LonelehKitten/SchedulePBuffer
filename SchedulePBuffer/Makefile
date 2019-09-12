all: main.o schedule.o
	gcc main.o schedule.o -o main

gdb: main.o schedule.o
	gcc main.o schedule.o -o main -g

main.o: main.c
	gcc -c main.c -o main.o

schedule.o: schedule.c
	gcc -c schedule.c -o schedule.o