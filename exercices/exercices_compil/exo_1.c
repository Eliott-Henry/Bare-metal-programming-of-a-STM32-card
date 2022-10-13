#include <stdint.h>

int g(){
    return 0;
}

uint32_t a; // global variable

__attribute__((naked)) void f() {
    for (unsigned int i=0; i<=a; i++)
    g();
}