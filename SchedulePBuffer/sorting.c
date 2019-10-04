#include "sorting.h"

void InsertionSort(ULint * n){ 

    ULint * i = (ULint *) (ULINT(1));
    ULint * j = (ULint *) (ULINT(2));

    Schedule * aux = (Schedule *) ULINT(7);

    for ((*i) = 1; (*i) < (*n); (*i)++){  
        move( aux, SORT(*i) );
        (*j) = (*i) - 1;

        while ((*j) >= 0 && match( SORT(*j)->name , aux->name )){  
            move( SORT(*j+1), SORT(*j) );  
            (*j)--;
        }  
        move(SORT(*j+1), aux);  
    }  
}

void SelectionSort(ULint * n){
    ULint * i, * j, * k;
    Schedule * s1, * s2, * aux;

    i = (ULint *) ULINT(1);
    j = (ULint *) ULINT(2);
    k = (ULint *) ULINT(4);

    aux = (Schedule *) ULINT(7);
  
    for((*i) = 0; (*i) < (*n)-1; (*i)++){

        (*k) = (*i);

        for((*j) = (*i)+1; (*j) < (*n); (*j)++){
            s1 = SORT(*k);
            s2 = SORT(*j);
            if ( match(s2->name, s1->name) )
                (*k) = (*j);
        }

        s2 = SORT(*i);

        move(aux, s1);
        move(s1, s2);
        move(s2, aux);
    } 
}

void copy(ULint * n){
    sorting = malloc((*n)*sizeof(Schedule));

    ULint * i = (ULint *) (ULINT(2));

    for( (*i) = 0; (*i) < (*n); (*i)++){

        move(SORT(*i), SCHEDULE(*i));

    }

    for(int h = 0; h < 4; h++) printf("\n%s\n", SORT(h)->name);

}

void move(Schedule * to, Schedule * from){
    to->id = from->id;
    strcpy(to->name, from->name);
    to->age = from->age;
    to->cep = from->cep;
}

int match(char * a, char * b){
    ULint * m = (ULint *) ULINT(6);

    for((*m) = 0; (*m) < strlen(a); (*m)++) a[(*m)] = tolower(a[(*m)]);
    for((*m) = 0; (*m) < strlen(b); (*m)++) b[(*m)] = tolower(b[(*m)]);

    (*m) = 0;

    printf("\n%d\n", (int) a[(*m)] > b[(*m)]);
    if (strcmp(b, a) > 0){
        return 1;
    }
    return 0;
    /*while(1){
        if( (*m) < ( strlen(a) < strlen(b) ? strlen(a) : strlen(b) ) &&  a[(*m)] > b[(*m)])
            return 1;
        else if(a[(*m)] < b[(*m)] || (*m) == ( strlen(a) < strlen(b) ? strlen(a) : strlen(b) ))
            break;
        else if (a[(*m)] == b[(*m)])
            (*m)++;
    }
    */
    return 0;
}

void show(ULint * n){

    ULint * i = (ULint *) (ULINT(2));
    ULint * k = (ULint *) (ULINT(4));
    Schedule * sc;

    for( (*i) = 0 ; (*i) < (*n); (*i)++){

        sc = SORT(*i);

        sc->name[0] = toupper( sc->name[0] );
        for((*k) = 0; sc->name[*k] && sc->name[*k+1]; (*k)++){
            if(sc->name[*k] == ' ') sc->name[*k+1] = toupper( sc->name[*k+1] );
        }

        printf("\n\n\t==== [ %ld ] ================\n", sc->id);
        printf("\n\t\tNome:    %s", sc->name);
        printf("\n\t\tIdade:   %d", sc->age);
        printf("\n\t\tCEP:     %d", sc->cep);
    }

    free(sorting);
}