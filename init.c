extern char __bss_start, __bss_end;

void init_bss(){
    char *p = &__bss_start;
    while(p< &__bss_end){
        *p = 0;
        p++;
    }
}