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

#define END pBuffer
#define ULINT(I) (pBuffer+(I)*sizeof(ULint))
#define SCHEDULE(S) ( (pBuffer+7*sizeof(ULint)+sizeof(Schedule)) + (S)*sizeof(Schedule) )

#endif /* BUFFER_H */