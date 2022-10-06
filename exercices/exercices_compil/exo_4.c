#include <stdint.h>
#include <stdio.h>

int32_t x = 34; // Data
int32_t y; // Bss
const char mesg[] = "Hello World!\n"; // Rodata 

int main() {
    static uint8_t z; // Bss ?
    uint16_t t;

    y = 12;
    z = z + 1;
    t = y+z;

    printf(mesg);
    printf("x = %d, y = %d, z = %d, t = %d\n",
           x, y, z, t);
    return 0;
}


/*
-Os : optimisation en taille 
Text 00000000
.text.startup 00000068
Data 00000004
Bss 00000005
rodata 0000000e
rodata.str1.1 0000002d

-O0 : pas d'opti
text 000000b8
Data 00000004 
Bss 00000005
Rodata 00000040

-01 :
Text 0000006c
Data 00000004
bss 00000005 
Rodata.str1.4 00000030
Rodata 0000000e 


-02 : 
Text 00000000
.text.startup 0000006c 
Data 00000004
Bss 00000005
Rodata.str1.4 00000030
Rodata 0000000e

Pour les tailles de la section text :
- Os a la plus petite car c'est le but de cette optimisation $
- O0 a l aplus grande car on n'a rien optimisé
- O1 et O2 ont la même aussi (à partir de l'opti O2 il y a peu de différences) 

Pour la taille de data :
Elle vaut 4 partout
(un int sur 32 bits donc 4 octets)
L'optimisation n'a pas d'effet

Pour la taille de Rodata :
On a une chaîne de 13 caractères donc 14 avec \0 donc au moins 14 octets
Selon les optimisations on a plus ou moins
- Plus petite dans 0s car c'est le but
- Plus grande dans O0 car pas optimisé
- Egale pour O1 et O2

Pour la taille de bss : 
Elle vaut 5 partout
(un int sur 32 bits donc 4 octets et la variable static z sur 8 bits donc 1 octet)
L'optimisation n'a pas d'effet
*/