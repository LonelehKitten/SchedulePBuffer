#include "sorting.h"

void InsertionSort(unsigned int * n){ 

    ULint * i = (ULint *) (ULINT(1));
    ULint * j = (ULint *) (ULINT(2));

    Schedule * aux = (Schedule *) ULINT(7);

    for (*i) = 1; (*i) < (*n); (*i)++){  
        swap( aux, (Schedule *)(sorting+(*i)*sizeof(Schedule)) );
        (*j) = (*i) - 1;

        while ((*j) >= 0 && match(aux->name, ((Schedule *)(sorting+(*j)*sizeof(Schedule)))->name )){  
            swap( (Schedule *) (sorting+( (*j)+1 )*sizeof(Schedule)), (Schedule *) (sorting+(*j)*sizeof(Schedule)) );  
            (*j) = (*j) - 1;
        }  
        swap((Schedule *) (sorting+( (*j)+1 )*sizeof(Schedule)), aux);  
    }  
}

void SelectionSort(unsigned int * n){
    ULint * i, * j, * k;
    Schedule * s1, * s2, * aux;

    i = (ULint *) ULINT(1);
    j = (ULint *) ULINT(2);
    k = (ULint *) ULINT(4);

    aux = (Schedule *) ULINT(7);
  
    for((*i) = 0; (*i) < (*n)-1; (*i)++){

        (*k) = (*i);

        for((*j) = (*i)+1; (*j) < (*n); (*j)++){
            s1 = (Schedule *) (sorting+(*k)*sizeof(Schedule));
            s2 = (Schedule *) (sorting+(*j)*sizeof(Schedule));
            if ( match(s2->name, s1->name) )
                (*k) = (*j);
        }

        s2 = (Schedule *) (sorting+(*i)*sizeof(Schedule));

        swap(aux, s1);
        swap(s1, s2);
        swap(s2, aux);
    } 
}

void copy(unsigned int * n){
    sorting = malloc((*n)*sizeof(Schedule));

    ULint * i = (ULint *) (ULINT(2));

    Schedule * sort_aux, * buffer_aux;

    for(*i = 0; *i < (*n); (*i)++){
        
        sort_aux   = (Schedule *) (sorting + (*i)*sizeof(Schedule));
        buffer_aux = (Schedule *) SCHEDULE(*i);

        swap(sort_aux, buffer_aux);

    }

}

void swap(Schedule * to, Schedule * from){
    to->id = from->id;
    strcpy(to->name, from->name);
    to->age = from->age;
    to->cep = from->cep;
}

int match(char * a, char * b){
    strcpy(a, tolower(a));
    strcpy(b, tolower(b));

    ULint * m = (ULint *) ULINT(6);
    (*m) = 0;

    while(true){
        if( (*m) < ( strlen(a) < strlen(b) ? strlen(a) : strlen(b) ) &&  b[(*m)] > a[(*m)])
            return 1;
        else if((*m) == ( strlen(a) < strlen(b) ? strlen(a) : strlen(b) ))
            break;
        else
            (*m)++;
    }

    return 0;
}