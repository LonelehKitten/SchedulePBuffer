#include "schedule.h"

int main(void) {

  ULint * op = init();

  do{

    menu(op);

    switch(*op){
      case 1:
        put();
        break;
      case 2:
        pop();
        break;
      case 3:
        search();
        break;
      case 4:
        list();
        break;
    }

    op = pBuffer+sizeof(ULint);

  } while(*op);

  free(pBuffer);

  return 0;
}