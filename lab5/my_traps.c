#include <stdint.h>
#include "syscall.h"
#include <stdlib.h>
#include <stdio.h>

uintptr_t handle_trap(uintptr_t epc, uintptr_t cause, uintptr_t tval, uintptr_t
regs[32])
{
    /* Extract low-order bits of exception code as positive int */
    int code = cause & ((1UL << ((sizeof(int)<<3)-1)) - 1);
    /* Encode interrupt as negative value */
    code = ((intptr_t)cause < 0) ? -code : code;
    printf("my traps\n");
    if (code == 11) {
            if (regs[10] == 10)
                    _exit(0);
    }
    _exit(code);
    __builtin_unreachable();
}
