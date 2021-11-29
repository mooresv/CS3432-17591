Example test program and starter solution for lab 5. 

To build and run using the chipyard installation on PSC Bridges-2, do the following:

source /ocean/projects/cis210002p/shared/chipyard/env-riscv-tools.sh
riscv64-unknown-elf-gcc -g -O2 -I$LIBGLOSS/include -std=c11 -pedantic -Wall -specs=$LIBGLOSS/util/htif.specs -L . -T $LIBGLOSS/util/htif.ld -Wl,-Map=ecall.riscv.map -o ecall.riscv ecall.s my_traps.c
spike ecall.riscv
