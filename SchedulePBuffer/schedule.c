#include "schedule.h"

/*

    END         -> pBuffer                  = last_schedule     (ULint)
    ULINT(1)    -> pBuffer+sizeof(ULint)    = aux1              (ULint)
    ULINT(2)    -> pBuffer+2*sizeof(ULint)  = aux2              (ULint)
    ULINT(3)    -> pBuffer+3*sizeof(ULint)  = aux3              (ULint)
    ULINT(4)    -> pBuffer+4*sizeof(ULint)  = aux1              (ULint)
    ULINT(5)    -> pBuffer+5*sizeof(ULint)  = aux2              (ULint)
    ULINT(6)    -> pBuffer+6*sizeof(ULint)  = aux3              (ULint)
    ULINT(7)    -> pBuffer+7*sizeof(ULint)  = aux schedule      (Schedule)
    BEGIN       -> pBuffer+7*sizeof(ULint)
                         +sizeof(Schedule)  = begin_schedule    (Schedule)

*/

/**
* Print menu options
**/
void menu(ULint * op){
  printf("\n\n\t\t==== AGENDA ====\n\n");
  printf("\t1) Cadastrar\n\t2) Remover\n\t3) Procurar\n\t4) Listar\n\t0) Sair\n\n\t\t>>>    ");
  scanf("%ld", op);
  getchar();
}

/**
* Initialize the pBuffer and its headers
**/
ULint * init(){
    END = (void *) malloc(4*sizeof(ULint) + sizeof(Schedule));
    *(ULint *)END = (ULint) (SCHEDULE(0));
    return ULINT(1);
}

/**
* Add register
**/
void put(){
    Schedule * s = allocSchedule();

    printf("\n\n\t\t==== CADASTRAR ====\n\n");
    printf("\tNome:    ");
    scanf("%[^\n]s", s->name);
    getchar();
    printf("\tIdade:    ");
    scanf("%d", &s->age);
    getchar();
    printf("\tCEP:    ");
    scanf("%d", &s->cep);
    getchar();
    printf("\n\tCadastro feito com sucesso!\n");
}

/**
* Remove register by id
**/
void pop(){

    ULint * id = (ULint *)(ULINT(3));

    printf("\n\n\t\t==== REMOVER ====\n\n");
    printf("\tID:    ");
    scanf("%ld", id);
    getchar();

    /* CHECKPOINT */

    if(*(ULint *)END != (ULint) SCHEDULE(0) && *id > 0 && *id <= ((Schedule *) ((*(ULint *)END)-sizeof(Schedule)))->id){
        
        destroySchedule(id);
        printf("\n\tCadastro removido com sucesso!\n");
    }
    else printf("\n\tCadastro não existente!\n");

}

/**
* Search register by name (can show most of one result, if most than one register are with the same name)
**/
void search(){
    char * name = (char *) malloc(30*sizeof(char));
    *(name+30) = '\0';

    printf("\n\n\t\t==== BUSCAR ====\n\n");
    printf("\tNome:    ");
    scanf("%[^\n]s", name);
    getchar();

    ULint * i = (ULint *) (ULINT(2));
    ULint * j = (ULint *) (ULINT(3));
    Schedule * sc;

    *j = (bufferLength() - 4*sizeof(ULint) - sizeof(Schedule)) / sizeof(Schedule);

    for(*i = 0; *i < *j; (*i)++){
        sc = (Schedule *) SCHEDULE(*i);
        if(strcmp( sc->name , name ) == 0){
          printf("\n\n\t==== [ %ld ] ================\n", sc->id);
          printf("\n\t\tNome:    %s", sc->name);
          printf("\n\t\tIdade:   %d", sc->age);
          printf("\n\t\tCEP:     %d", sc->cep);
        }
    }

    free(name);
}

/**
* Show all registers
**/
void list(){

    ULint * i = (ULint *) (ULINT(2));
    ULint * j = (ULint *) (ULINT(3));
    Schedule * sc;

    do{
        printf("\n\n\t\t==== LISTAR ====\n\n");
        printf("\t1) Insertion Sort\n\t2) Selection Sort\n\t0) Sem Ordenação\n\n\t\t>>>    ");
        scanf("%ld", i);
    }while( (*i) < 0 && (*i) > 2);
    
    *j = (bufferLength() - 4*sizeof(ULint) - sizeof(Schedule)) / sizeof(Schedule);

    if( !(*i) ){
        for( ; *i < *j; (*i)++){
            sc = (Schedule *) SCHEDULE(*i);
            printf("\n\n\t==== [ %ld ] ================\n", sc->id);
            printf("\n\t\tNome:    %s", sc->name);
            printf("\n\t\tIdade:   %d", sc->age);
            printf("\n\t\tCEP:     %d", sc->cep);
        }
    }
    else if((*i) == 1){
        copy(j);
        InsertionSort(j);
    }
    else if((*i) == 2){
        copy(j);
        SelectionSort(j);
    }
    
}

/* ==== UTILS ==== */

/**
* Allocs new Schedule structure
**/
Schedule * allocSchedule(){
    END = realloc(END, bufferLength()+sizeof(Schedule));
    *(ULint *) END = (ULint) ( SCHEDULE(0) + ( (*(ULint *)(ULINT(2))) - 4*sizeof(ULint)) ); //+ sizeof(Schedule);

    Schedule * sc;
  
    ULint * j = (ULint *) (ULINT(2));
    ULint * k = (ULint *) (ULINT(3));

    *k = (bufferLength() - 4*sizeof(ULint) - sizeof(Schedule)) / sizeof(Schedule);

    for(*j = 1; *j < (*k); (*j)++){
        sc = (Schedule *) SCHEDULE(*j-1);
        if(*j == 1 && sc->id != *j) break;
        if( *j+1 != *k && ( (Schedule *) ( ((ULint)sc)+sizeof(Schedule) ) )->id - sc->id > 1){(*j)++; break;}
    }
    
    for(; *k > *j; (*k)--){
        sc = (Schedule *) SCHEDULE(*k-1);
        // id
        sc->id = ( (Schedule *) ( ((ULint)sc)-sizeof(Schedule) ) )->id;
        // name
        strcpy(sc->name, ( (Schedule *) ( ((ULint)sc)-sizeof(Schedule) ) )->name);
        // age
        sc->age = ( (Schedule *) ( ((ULint)sc)-sizeof(Schedule) ) )->age;
        // cep
        sc->cep = ( (Schedule *) ( ((ULint)sc)-sizeof(Schedule) ) )->cep;
    }

    sc =  (Schedule *) SCHEDULE(*j-1);
    sc->id = *j;
    
    return sc;
}

/**
* Destroy a Schedule structure
**/
void destroySchedule(ULint * id){
    *(ULint *)(ULINT(1)) = *id; // save the choosen schedule id

    END = (void *) realloc(END, bufferLength()-sizeof(Schedule));
    *(ULint *) END = (ULint) ( SCHEDULE(0) + ( (*(ULint *)(ULINT(2))) - 4*sizeof(ULint)) ) - 2*sizeof(Schedule); // recover the last created schedule by the buffer length saved

    *id = *(ULint *)(ULINT(1)); // recover saved id
    *id = (ULint) SCHEDULE(*id-1); // take the address by the saved id
    // IMPORTANT: From here, the pointer "id" starts to work as "dead schedule address".

    for(; *id < * (ULint*) END; *id += sizeof(Schedule)){ // shift the schedules to left
        ((Schedule *) *id)->id = ((Schedule *) (*id+sizeof(Schedule)))->id;
        strcpy( ((Schedule *) *id)->name, ((Schedule *) (*id+sizeof(Schedule)))->name );
        ((Schedule *) *id)->age = ((Schedule *) (*id+sizeof(Schedule)))->age;
        ((Schedule *) *id)->cep = ((Schedule *) (*id+sizeof(Schedule)))->cep;
    }

    strcpy(( (Schedule *) (*(ULint *)END) )->name, "\0");
    ( (Schedule *) (*(ULint *)END) )->id = 0;
}

/**
* Return the buffer length, since the first byte until the last byte of the last Schedule
**/
ULint bufferLength(){
  ULint * l = (ULint *) (ULINT(2));
  ULint * a = (ULint *) (ULINT(3));

  *l = 4*sizeof(ULint);

  for(*a = (ULint) SCHEDULE(0); *a <= *(ULint *)END; *a += sizeof(Schedule))
    *l += sizeof(Schedule);

  return *l;
}