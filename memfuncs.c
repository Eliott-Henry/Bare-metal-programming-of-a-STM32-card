#include <stddef.h>
#include <stdint.h>

void * memset(void *s, int c, size_t n){
    uint8_t *p = (uint8_t) s;
    int i;
    for (i = 0; i<n;i++){
        p[i] = (uint8_t) c;
    }
    return s;
}