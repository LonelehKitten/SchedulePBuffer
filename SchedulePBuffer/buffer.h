#ifndef BUFFER_H
#define BUFFER_H

typedef unsigned long int ULint;

typedef struct schedule{
  ULint id;
  char name[100];
  int age;
  int cep;
} Schedule;

void * pBuffer;

#endif /* BUFFER_H */