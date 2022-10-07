extern int __bss_start, __bss_end;
int a; // va dans la bss 

void init_bss(){
    int *p = &__bss_start;
    while(p < &__bss_end){
        *p = 0;
        p++;
    }
    a = a + 1; // pour reconnaître les instructions en debug et vérifier que a vaut bien 0 au début
}