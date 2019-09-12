#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long int ULint;

typedef struct schedule{
  ULint id;
  char name[100];
  int age;
  int cep;
} Schedule;

void * pBuffer;

ULint * init(); // VIONH9IEWHGOIERB9O

void put();
void pop();
void search();
void list();

void menu(ULint * op);

Schedule * allocSchedule();
void destroySchedule(ULint * ids);

ULint bufferLength();

#endif /* SCHEDULE_H */