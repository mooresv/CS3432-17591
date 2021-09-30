CC=gcc
CFLAGS=-c -Wall
USE_TOKENIZER=true# <-- true if using a custom tokenizer, false otherwise
CUSTOM_TOKENIZER=tokenizer# <-- put your tokenizer.c file name without the file extension

all: riscv populate

populate: populate.o
	$(CC) populate.o -o populate

populate.o: populate.c
	$(CC) $(CFLAGS) populate.c -o populate.o

ifeq ($(USE_TOKENIZER),true)
riscv: memory.o $(CUSTOM_TOKENIZER).o riscv.o
	$(CC) riscv.o memory.o $(CUSTOM_TOKENIZER).o -o riscv
else
riscv: memory.o riscv.o
	$(CC) riscv.o memory.o -o riscv
endif

riscv.o: riscv.c
	$(CC) $(CFLAGS) riscv.c -o riscv.o

memory.o: memory.c
	$(CC) $(CFLAGS) memory.c -o memory.o

ifeq ($(USE_TOKENIZER),true)
$(CUSTOM_TOKENIZER).o: $(CUSTOM_TOKENIZER).c
	$(CC) $(CFLAGS) $(CUSTOM_TOKENIZER).c -o $(CUSTOM_TOKENIZER).o
endif

clean :
	rm riscv.o populate.o memory.o $(CUSTOM_TOKENIZER).o riscv populate mem.txt
