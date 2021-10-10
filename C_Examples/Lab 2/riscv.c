#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file
#include "riscv.h" // built-in functions for riscv operations
#include "string.h" 

#define MEMORY "mem.txt"

int32_t* reg; // Array of 32 32-bit registers


/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char instr[]){
	char** tokens = tokenize(trim(instr), ' '); // creates tokens using empty space as delim
	print_all_tokens(tokens);
	
	int is_mnemonic = mnemonic(tokens[0]); // gets the key for each mnemonic instruction operation 
	bool accepted;
	
	if(is_mnemonic!=-1){
		if(is_mnemonic==0){
			lw(tokens[1], tokens[2]);
			accepted = true;
		}
		if(is_mnemonic==1){
			sw(tokens[1], tokens[2]);
			accepted = true;
		}
		if(is_mnemonic==2){
			add(tokens[1], tokens[2], tokens[3]);
			accepted = true;
		}
		if(is_mnemonic==3){
			addi(tokens[1], tokens[2], tokens[3]);
			accepted = true;
		}
		if(is_mnemonic==4){
			and(tokens[1], tokens[2], tokens[3]);
			accepted = true;
		}
		if(is_mnemonic==5){
			or(tokens[1], tokens[2], tokens[3]);
			accepted = true;
		}
		if(is_mnemonic==6){
			xor(tokens[1], tokens[2], tokens[3]);
			accepted = true;
		}
		else{
			accepted = false;
		}
		


	}


	return accepted;
}

/* 
	LW -> 0
	SW -> 1
	ADD -> 2
	ADDI -> 3
	AND -> 4
	OR -> 5
	XOR -> 6
*/
int mnemonic(char* is_mnemonic) {

	// maps the instruction to its corresponding value
	if (compare(is_mnemonic, "LW")) {
		is_mnemonic= 0;
	} else if (compare(is_mnemonic, "SW")) {
		is_mnemonic= 1;
	} else if (compare(is_mnemonic, "ADD")) {
		is_mnemonic= 2;
	} else if (compare(is_mnemonic, "ADDI")) {
		is_mnemonic= 3;
	} else if (compare(is_mnemonic, "AND")) {
		is_mnemonic= 4;
	} else if (compare(is_mnemonic, "OR")) {
		is_mnemonic= 5;
	} else if (compare(is_mnemonic, "XOR")) {
		is_mnemonic= 6;
	}else {
		printf("Invalid instruction please enter another one: \n");
	}

	return -1;
}

/*
	Method that check is two string literals are the same
*/
bool compare(char* str1, char* str2) {
	int size_str1 = str_size(str1); 
	int size_str2 = str_size(str2);

	if (size_str1 != size_str2) { // not same size
		return false;
	} 

	int c;
	for (c = 0; c < size_str1 && str2[c] != '\0'; c++) { 
		if ((*str1) != (*str2)) { // chars don't match
			return false;
		}
		str1++;
		str2++;
	}
	return true;
}

/*
	Method that gets and adds the values from registers rs1 and rs2 and stores it in the destination register (rd)
*/
void add(char* rd, char* rs1, char* rs2) {
	int32_t rd_num = atoi(remove_x(rd)); // rd = destination register
	int32_t rs1_num = atoi(remove_x(rs1)); // rs1 = base addres register 1
	int32_t rs2_num = atoi(remove_x(rs2)); // rs2 = base addres register 2

	reg[rd_num] = reg[rs1_num] + reg[rs2_num]; // rd = rs1 + rs2. E.g x1 = x2 + x3
}

/*
	Method that gets and adds the values from registers rs1 and imm and stores it in the destination register (rd)
*/
void addi(char* rd, char* rs1, char* imm) {
	int32_t rd_num = atoi(remove_x(rd));
	int32_t rs1_num = atoi(remove_x(rs1));
	int32_t imm_num = atoi(imm); // imm = immediate value
	
	reg[rd_num] = reg[rs1_num] + imm_num; // rd = rs1 + imm. E.g x1 = x2 + 5
}

/*
	lw (load word) loads a word from memory to a register.
*/
void lw(char* rd, char* rs1_imm) {
	char** tokens = tokenize(rs1_imm, '('); // creates tokens using open parenthesis as delim
	print_all_tokens(tokens);

	char* rs1 = tokens[1];
	char* imm = tokens[0];

	int32_t rd_num = atoi(remove_x(rd));
	int32_t imm_num = atoi(imm); 
	int32_t rs1_num = atoi(remove_x(rs1));

	int32_t address = imm_num + reg[rs1_num]; // address = imm + rs1's value
	int32_t data = read_address(address, MEMORY); // data = returns the memory's value using the address
	
	reg[rd_num] = data; // stores the memory's value into rd 
}

/*
	sw (store word) stores a register into memory.
*/
void sw(char* rd, char* rs1_imm) {
	char** tokens = tokenize(rs1_imm, '('); // creates tokens using open parenthesis as delim
	print_all_tokens(tokens);

	char* rs1 = tokens[1];
	char* imm = tokens[0];

	int32_t rd_num = atoi(remove_x(rd));
	int32_t imm_num = atoi(imm); 
	int32_t rs1_num = atoi(remove_x(rs1));

	int32_t address = imm_num + reg[rs1_num]; // address = imm + rs1's value
	int32_t data = reg[rd_num]; // data = rd

	write_address(data, address, MEMORY); // stores rd's value into memory's address
}

/*
	Method that gets and ANDs the values from registers rs1 and rs2 and stores it in the destination register (rd)
*/
void and(char* rd, char* rs1, char* rs2) {
	int32_t rd_num = atoi(remove_x(rd));
	int32_t rs1_num = atoi(remove_x(rs1));
	int32_t rs2_num = atoi(remove_x(rs2));

	reg[rd_num] = reg[rs1_num] & reg[rs2_num]; // rd = rs1 & rs2 
}

/*
	Method that gets and ORs the values from registers rs1 and rs2 and stores it in the destination register (rd)
*/
void or(char* rd, char* rs1, char* rs2) {
	int32_t rd_num = atoi(remove_x(rd));
	int32_t rs1_num = atoi(remove_x(rs1));
	int32_t rs2_num = atoi(remove_x(rs2));

	reg[rd_num] = reg[rs1_num] | reg[rs2_num]; // rd = rs1 | rs2 
}

/*
	Method that gets and XORs the values from registers rs1 and rs2 and stores it in the destination register (rd)
*/
void xor(char* rd, char* rs1, char* rs2) {
	int32_t rd_num = atoi(remove_x(rd));
	int32_t rs1_num = atoi(remove_x(rs1));
	int32_t rs2_num = atoi(remove_x(rs2));

	reg[rd_num] = reg[rs1_num] ^ reg[rs2_num]; // rd = rs1 XOR (^) rs2 
}

/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

//Prints all the registers from the regs array
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}


/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	//print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();

	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");

	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}

/*
	Method used to remove char 'X' from parameter string
*/
char* remove_x(char* str) {
	char* temp = str;
	while(*temp == 'X') {
		temp++;
	}
	return temp;
}
