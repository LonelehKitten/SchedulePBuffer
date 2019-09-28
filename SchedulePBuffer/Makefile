all: main.o schedule.o sorting.o
	gcc main.o schedule.o sorting.o -o main

gdb: main.o schedule.o
	gcc main.o schedule.o -o main -g

main.o: main.c
	gcc -c main.c -o main.o

schedule.o: schedule.c
	gcc -c schedule.c -o schedule.o

sorting.o: sorting.c
	gcc -c sorting.c -o sorting.o