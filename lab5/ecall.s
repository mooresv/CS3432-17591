        .text
        .globl  main
        .type   main, @function
main:
        addi    sp,sp,-32
        sd      ra,0(sp)
        li      a0,9
        li      a1,4
        ecall
        li      a4,5
        sd      a4,0(a0)
        ld      a1,0(a0)
        li      a0,1
        ecall
        ld      ra,0(sp)
        addi    sp,sp,32
        li      a0, 10
        ecall
