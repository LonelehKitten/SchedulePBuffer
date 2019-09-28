#ifndef SORTING_H
#define SORTING_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "buffer.h"

void * sorting;

void InsertionSort(ULint * n);
void SelectionSort(ULint * n);
void copy(ULint * n);
void swap(Schedule * to, Schedule * from);
int match(char * a, char * b);

#endif /* SORTING_H */