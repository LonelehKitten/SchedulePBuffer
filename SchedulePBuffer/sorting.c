#include "sorting.h"

void InsertionSort(unsigned int * n){
    
    
}

void SelectionSort(unsigned int * n){

}

void copy(unsigned int * n){
    sorting = malloc((*n)*sizeof(Schedule));

    int * i = (ULint *) (pBuffer+2*sizeof(ULint));

    Schedule * sort_aux, * buffer_aux;

    for(*i = 0; *i < (*n); (*i)++){
        
        sort_aux   = (Schedule *)(sorting + (*i)*sizeof(Schedule));
        buffer_aux = (Schedule *)((pBuffer+4*sizeof(ULint)) + (*i)*sizeof(Schedule));

        sort_aux->id = buffer_aux->id;
        strcpy(sort_aux->name, buffer_aux->name);
        sort_aux->age = buffer_aux->age;
        sort_aux->cep = buffer_aux->cep;

    }

}