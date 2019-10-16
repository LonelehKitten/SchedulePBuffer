#include "sorting.h"

void InsertionSort(ULint * n){ 

    ULint * i = (ULint *) (ULINT(1));
    ULint * j = (ULint *) (ULINT(2));

    Schedule * aux = (Schedule *) ULINT(7);

    for((*i) = 1; (*i) < (*n); (*i)++){  
        move( aux, SORT(*i) );
        (*j) = (*i) - 1;

        while( (int) (*j) >= 0 && match( SORT(*j)->name, aux->name ) > 0){ 
            printf("\n---\n") ;
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
        s1 = SORT(*k);
        
        for((*j) = (*i)+1; (*j) < (*n); (*j)++){
            
            s2 = SORT(*j);
            if ( match(s2->name, s1->name) < 0){
                (*k) = (*j);
                s1 = SORT(*k);
            }
        }

        s2 = SORT(*i);

        move(aux, s1);
        move(s1, s2);
        move(s2, aux);
    } 
}

void BubbleSort(ULint * n){

    ULint * i = (ULint *) (ULINT(1));
    ULint * j = (ULint *) (ULINT(2));

    Schedule * aux = (Schedule *) ULINT(7);

    for((*i) = 0; (*i) < (*n)-1; (*i)++){
        for((*j) = 0; (*j) < (*n)-(*i)-1; (*j)++){
            if( match( SORT(*j)->name, SORT(*j+1)->name ) > 0 ){
                move( aux, SORT(*j) );
                move( SORT(*j), SORT(*j+1) );
                move( SORT(*j+1), aux );
            }
        }
    }
}

void QuickSort(ULint * n, Schedule * left, Schedule * right){

    Schedule * i, * j, * aux, * middle;

    i = left ? left : SORT(0) ;
    j = right ? right : SORT(*n-1);

    middle = SORT(( ((ULint) j) - ((ULint) i) + sizeof(Schedule) )/2*sizeof(Schedule));

    aux = (Schedule *) ULINT(7);

    do{

        while(match(i->name, middle->name) < 0)
            i += sizeof(Schedule);

        while(match(j->name, middle->name) > 0)
            j -= sizeof(Schedule);

        if( i <= j ){
            move(aux, i);
            move(i, j);
            move(j, aux);
            i += sizeof(Schedule);
            j -= sizeof(Schedule);
        }

    }while( i <= j );

    if(left < j)
        QuickSort(NULL, left, j);

    if(i < right)
        QuickSort(NULL, i, right);

}

void copy(ULint * n){
    sorting = malloc((*n)*sizeof(Schedule));

    ULint * i = (ULint *) (ULINT(2));

    for( (*i) = 0; (*i) < (*n); (*i)++){

        move(SORT(*i), SCHEDULE(*i));

    }

    //for(h = 0; h < 4; h++) printf("\n%s\n", SORT(h)->name);

}

void move(Schedule * to, Schedule * from){
    printf("\n move() -> begin [ %s <-> %s ] ", to->name, from->name);
    to->id = from->id;
    strcpy(to->name, from->name);
    to->age = from->age;
    to->cep = from->cep;
    printf("=> end\n");
}

int match(char * a, char * b){
    ULint * m = (ULint *) ULINT(6);

    for((*m) = 0; (*m) < strlen(a); (*m)++) a[(*m)] = tolower(a[(*m)]);
    for((*m) = 0; (*m) < strlen(b); (*m)++) b[(*m)] = tolower(b[(*m)]);

    (*m) = 0;

    printf("\n%d\n", (int) a[(*m)] > b[(*m)]);
    return strcmp(a, b);
    
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