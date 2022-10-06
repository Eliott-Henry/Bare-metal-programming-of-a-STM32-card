#include <stdio.h>
#include <stdlib.h>

/*
Dans ce code, on créé des variables et des constantes en sachant dans quelle section elles seront placées.
Ensuite, on écrit leur adresse pour savoir quel est l'ordre des sections.
Pour la section texte, on utilise objdump et on regarde à quelle adresse est le code.
*/

const int a = 1; /* constante donc dans rodata */
int b; /* variable non initialisée donc dans bss */
int c = 3; /* variable initialisée donc dans data */

void f(){
    int s1 = 1;
    int s2 = 2;
    int * stack1 = &s1;
    int * stack2 = &s2;
    printf("Stack 1: %p\n", stack1);
    printf("Stack 2: %p\n", stack2);
}

int main(){
    f();
    int const * rodata = &a;
    int * bss = &b;
    int * data = &c;
    int * heap = malloc(sizeof(int));

    printf("Text : %p\n", main);
    printf("Rodata : %p\n", rodata);
    printf("Bss : %p\n", bss);
    printf("Data : %p\n", data);
    printf("Heap : %p\n", heap);

    return 0;
}

/* Dans l'ordre, on trouve alors :
Text,rotada,data,bss,heap,stack 
De plus, la pile descend car adresse(s2) < adresse(s1) */