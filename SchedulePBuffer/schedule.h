#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

ULint * init();

void put();
void pop();
void search();
void list();

void menu(ULint * op);

Schedule * allocSchedule();
void destroySchedule(ULint * ids);

ULint bufferLength();



#endif /* SCHEDULE_H */