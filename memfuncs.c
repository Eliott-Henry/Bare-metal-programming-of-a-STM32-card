#include <stddef.h>
#include <stdint.h>

void * memset(void * source, int c, size_t size){
    uint8_t *p = (uint8_t *) size;
    for (int i = 0; i>=0 && (size_t)i < size;i++){
        p[i] = (uint8_t) c;
    }
    return source;
}

void * memcpy(void * restrict destination, const void * restrict source, size_t size){
    uint8_t *p = destination;
    const uint8_t * q = source;
    for(int i =0; i>=0 && (size_t)i < size; i++){
        *p = *q;
        p++;
        q++;
    }
    return destination;
}

void * memmove(void * destination, const void * source, size_t size){
    if(destination<source){
        memcpy(destination, source, size);
    }
    else{
        uint8_t *p = destination + size -1;
        const uint8_t *q = source + size -1;
        for(int i = 0; i>=0 && (size_t)i < size; i++){
            *p = *q;
            p--;
            q--;
        }
    }
    return destination;
}

int memcmp(const void * pointer1, const void * pointer2, size_t size){
    
    const uint8_t *p = pointer1;
    const uint8_t *q = pointer2;

    for(int i =0; i>=0 && (size_t)i < size; i++){
        if(*p < *q){
            return -1;
        }
        else if(*p > *q) {
            return 1;
        }
    }

    return 0;
}