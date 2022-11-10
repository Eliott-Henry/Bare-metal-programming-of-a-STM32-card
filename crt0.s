    .syntax unified
    .global _start
    .thumb

.thumb_func
_start:
    ldr sp, = _stack_start
    bl init_data
    bl init_bss
    bl main

_exit:
    b _exit