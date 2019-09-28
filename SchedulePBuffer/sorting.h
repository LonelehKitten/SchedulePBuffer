#ifndef SORTING_H
#define SORTING_H

#include <string.h>
#include <ctype.h>

#include "buffer.h"

void * sorting;

void InsertionSort(unsigned int * n);
void SelectionSort(unsigned int * n);
void copy(unsigned int * n);
void swap(Schedule * to, Schedule * from);
int match(char * a, char * b);

#endif /* SORTING_H */