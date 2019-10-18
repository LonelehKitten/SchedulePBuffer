#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "buffer.h"

void * sorting;

void InsertionSort(ULint * n);
void SelectionSort(ULint * n);
void BubbleSort(ULint * n);
void QuickSort(ULint * n, Schedule * left, Schedule * right);
void MergeSort(ULint * n, Schedule * left, Schedule * right);
void copy(ULint * n);
void move(Schedule * to, Schedule * from);
int match(char * a, char * b);
void show(ULint * n);

#define SORT(I) ( (Schedule *) (sorting+(I)*sizeof(Schedule)) )

#endif /* SORTING_H */