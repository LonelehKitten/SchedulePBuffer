#include "schedule.h"

/*

    pBuffer                 = last_schedule     (ULint)
    pBuffer+sizeof(ULint)   = aux1              (ULint)
    pBuffer+2*sizeof(ULint) = aux2              (ULint)
    pBuffer+3*sizeof(ULint) = aux3              (ULint)
    pBuffer+4*sizeof(ULint) = begin_schedule    (Schedule)

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
    pBuffer = (void *) malloc(4*sizeof(ULint) + sizeof(Schedule));
    *(ULint *)pBuffer = (ULint) (pBuffer+4*sizeof(ULint));
    return pBuffer+sizeof(ULint);
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

    ULint * id = (ULint *)(pBuffer+3*sizeof(ULint));

    printf("\n\n\t\t==== REMOVER ====\n\n");
    printf("\tID:    ");
    scanf("%ld", id);
    getchar();

    /* CHECKPOINT */

    printf("\n\n%ld != %ld, %ld <= %ld\n\n", *(ULint *)pBuffer,  (ULint) pBuffer+4*sizeof(ULint), *id,  ( (Schedule *) ((*(ULint *)pBuffer)-sizeof(Schedule)) )->id);

    if(*(ULint *)pBuffer != (ULint) pBuffer+4*sizeof(ULint) && *id > 0 && *id <= ((Schedule *) ((*(ULint *)pBuffer)-sizeof(Schedule)))->id){
        
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

    ULint * i = (ULint *) (pBuffer+2*sizeof(ULint));
    ULint * j = (ULint *) (pBuffer+3*sizeof(ULint));
    Schedule * sc;

    *j = (bufferLength() - 4*sizeof(ULint) - sizeof(Schedule)) / sizeof(Schedule);

    for(*i = 0; *i < *j; (*i)++){
        sc = (Schedule *) (pBuffer+4*sizeof(ULint))+(*i)*sizeof(Schedule);
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
    printf("\n\n\t\t==== LISTAR ====\n\n");

    ULint * i = (ULint *) (pBuffer+2*sizeof(ULint));
    ULint * j = (ULint *) (pBuffer+3*sizeof(ULint));
    Schedule * sc;

    *j = (bufferLength() - 4*sizeof(ULint) - sizeof(Schedule)) / sizeof(Schedule);

    printf("\n\n%ld\n\n", *j);

    for(*i = 0; *i < *j; (*i)++){
        sc = (Schedule *) ((pBuffer+4*sizeof(ULint))+(*i)*sizeof(Schedule));
        printf("\n\n%ld = %ld+4*%ld+%ld*%ld ", (ULint)(pBuffer+4*sizeof(ULint))+(*i)*sizeof(Schedule), (ULint)pBuffer, sizeof(ULint), (*i), sizeof(Schedule));
        printf("\n\n\t==== [ %ld ] ================\n", sc->id);
        printf("\n\t\tNome:    %s", sc->name);
        printf("\n\t\tIdade:   %d", sc->age);
        printf("\n\t\tCEP:     %d", sc->cep);
    }

}

/* ==== UTILS ==== */

/**
* Allocs new Schedule structure
**/
Schedule * allocSchedule(){
    pBuffer = realloc(pBuffer, bufferLength()+sizeof(Schedule));
    *(ULint *) pBuffer = (ULint) ( pBuffer+4*sizeof(ULint) + ( (*(ULint *)(pBuffer+2*sizeof(ULint))) - 4*sizeof(ULint)) ); //+ sizeof(Schedule);

    Schedule * sc;
  
    ULint * j = (ULint *) (pBuffer+2*sizeof(ULint));
    ULint * k = (ULint *) (pBuffer+3*sizeof(ULint));

    *k = (bufferLength() - 4*sizeof(ULint) - sizeof(Schedule)) / sizeof(Schedule);

    for(*j = 1; *j < (*k); (*j)++){
        sc = (Schedule *) ((ULint) (pBuffer+4*sizeof(ULint)) +  (*j-1)*sizeof(Schedule));
        if(*j == 1 && sc->id != *j) break;
        if( *j+1 != *k && ( (Schedule *) ( ((ULint)sc)+sizeof(Schedule) ) )->id - sc->id > 1) {
            printf("\n\n j: %ld, j++: %ld", *j, *j+1);
            (*j)++; break;
            }
    }

    printf("\n\n %ld / %ld / %ld\n\n", *j, *k, ((ULint) (pBuffer+4*sizeof(ULint)) +  (*j-1)*sizeof(Schedule)));
    printf("\n\n arit: (ULint) %ld+4*%ld +  %ld*%ld = %ld\n\n", (ULint) pBuffer, sizeof(ULint), *j-1, sizeof(Schedule), ((ULint) (pBuffer+4*sizeof(ULint)) +  (*j-1)*sizeof(Schedule)));

    //*j++;
    
    for(; *k > *j; (*k)--){
        sc =  (Schedule *) ((ULint) (pBuffer+4*sizeof(ULint)) + (*k-1)*sizeof(Schedule));
        // id
        sc->id = ( (Schedule *) ( ((ULint)sc)-sizeof(Schedule) ) )->id;
        // name
        strcpy(sc->name, ( (Schedule *) ( ((ULint)sc)-sizeof(Schedule) ) )->name);
        // age
        sc->age = ( (Schedule *) ( ((ULint)sc)-sizeof(Schedule) ) )->age;
        // cep
        sc->cep = ( (Schedule *) ( ((ULint)sc)-sizeof(Schedule) ) )->cep;
    }

    sc =  (Schedule *) ((ULint) (pBuffer+4*sizeof(ULint)) + (*j-1)*sizeof(Schedule));
    sc->id = *j;
    
    return sc;
}

/**
* Destroy a Schedule structure
**/
void destroySchedule(ULint * id){
    *(ULint *)(pBuffer+sizeof(ULint)) = *id; // save the choosen schedule id

    pBuffer = (void *) realloc(pBuffer, bufferLength()-sizeof(Schedule));
    *(ULint *) pBuffer = (ULint) ( pBuffer+4*sizeof(ULint) + ( (*(ULint *)(pBuffer+2*sizeof(ULint))) - 4*sizeof(ULint)) ) - 2*sizeof(Schedule); // recover the last created schedule by the buffer length saved

    *id = *(ULint *)(pBuffer+sizeof(ULint)); // recover saved id
    *id = (ULint) ((pBuffer+4*sizeof(ULint))+(*id-1)*sizeof(Schedule)); // take the address by the saved id
    // IMPORTANT: From here, the pointer "id" starts to work as "dead schedule address".

    printf("\n\nlast: %ld    :    choosen: %ld\n\n", * (ULint*) pBuffer, *id);

    for(; *id < * (ULint*) pBuffer; *id += sizeof(Schedule)){ // shift the schedules to left
        ((Schedule *) *id)->id = ((Schedule *) (*id+sizeof(Schedule)))->id;
        strcpy( ((Schedule *) *id)->name, ((Schedule *) (*id+sizeof(Schedule)))->name );
        ((Schedule *) *id)->age = ((Schedule *) (*id+sizeof(Schedule)))->age;
        ((Schedule *) *id)->cep = ((Schedule *) (*id+sizeof(Schedule)))->cep;
    }

    strcpy(( (Schedule *) (*(ULint *)pBuffer) )->name, "\0");
    ( (Schedule *) (*(ULint *)pBuffer) )->id = 0;
}

/**
* Return the buffer length, since the first byte until the last byte of the last Schedule
**/
ULint bufferLength(){
  ULint * l = (ULint *) (pBuffer+2*sizeof(ULint));
  ULint * a = (ULint *) (pBuffer+3*sizeof(ULint));

  *l = 4*sizeof(ULint);

  for(*a = (ULint) pBuffer+4*sizeof(ULint); *a <= *(ULint *)pBuffer; *a += sizeof(Schedule))
    *l += sizeof(Schedule);

  printf("\n\n%ld\n\n", *l);

  return *l;
}