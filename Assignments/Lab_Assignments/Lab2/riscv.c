#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers
char* input; //Array of chars to store user input
int input_size = 100; //size for input
char* instructions; //array of tokens
char lw[] = "LW";//words we are looking from first token
char sw[] = "SW";
char add[] = "ADD";
char addi[] = "ADDI";
const int lw_array_size = sizeof(lw)/sizeof(*lw);
const int sw_array_size = sizeof(sw)/sizeof(*sw);
const int add_array_size = sizeof(add)/sizeof(*add);
const int addi_array_size = sizeof(addi)/sizeof(*addi);	
//LW AND SW INSTRUCTIONS
char* word_from_memory;
char* rd;
char* rs1;
char* rs2;
char* imm;//it might be an address
int rd_int;
int32_t rs1_int;
int32_t rs2_int;
int32_t imm_int;

//Method declarations
void init_regs();
bool interpret(char* instr);
void write_read_demo();
bool compare_char_a(char* word_1, char* word_2, int comp_len);

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
//print registers
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}
//removes first character of a string or char array
char* rm_first_char(char* original){
	char* string_chopped = original+1;
	return string_chopped;
}
// Iterate through all digits and parse to int.
// value. multiply res by 10 to shuffle digits left.
// For each ASCII character of the digit: subtract the code from '0' to get numerical value.

//returns true if words are equal. given computarized length using sizeof(x)	
bool compare_char_a(char* word_1, char* word_2, int comp_len){
	int i;
	for(i = 0; i < comp_len; i++){
		if((word_1[i] == '\0')||(word_2[i] == '\0')){
			return false;
		}
		if(word_1[i] != word_2[i]){
			return false;
		}
	}
	return true;
}
/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){//instr is user input string
	instructions = strtok(input, " ");//tokenize user input
	printf("whats the instruction?:  \n%s\n", instructions[0]);
	if(instructions[0] == '\0'){//checks if the double-array is empty
		return false;
	}
	//ADD AND ADDI INSTRUCTION
	//if given the add instruction
	if((compare_char_a(add, instructions[0], add_array_size)) == (true)){
		rd = instructions[1];
		rs1 = instructions[2];
		rs2 = instructions[3];
		//remove unwanted chars 'X' and convert to int
		rd_int = atoi(rm_first_char(rd));
		printf("read number:  \n%d\n",rd_int);
		rs1_int = (int32_t) atoi(rm_first_char(rs1));
		printf("read number:  \n%d\n",rs1_int);
		rs2_int = (int32_t) atoi(rm_first_char(rs2));
		printf("read number:  \n%d\n",rs2_int);
		int32_t new_value = reg[rs1_int] + reg[rs2_int];
		printf("tha sum:  \n%d\n", new_value);
		//update contents of register
		reg[rd_int] = new_value;
	}
	//if given the addi instruction
	////if given the lw instruction
//	if((compare_char_a(lw, instructions[0], lw_array_size)) == (true) ){ //== REDUNDANT??
		//place holders:
//		char* mem_value;
//		char* new_location;
//
		//necessary variables for the instruction:
//		imm = instructions[3];
//		rs1_int = (int32_t) atoi(instructions[2]);
//		rd = instructions[1];
		
		//remove unwanted chars 'X' and convert to int:
//		rd = rm_first_char(rd);
//		imm = rm_first_char(imm);
		
		//convert values to integer
//		rd_int = (int32_t) atoi(rd);
//		imm_int = (int32_t) atoi(imm);
		
		//perform operation
//		mem_value = read_address(imm_int, "mem.txt");//getting value from memory
//		new_location = imm_int + rs1_int; //computing new destination for our value
//		reg[rd_int] = mem_value; //saving the value in register
//		
//		return true;//performed a successful operation
//	}
	//if given the sw instruction
	
	return false; //exit, unsuccessful opearation
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
	if(write == (int32_t) NULL){
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	}
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Your code goes in the main
 *
 */

int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE
	print_regs();
	// Below is a sample program to a write-read. Overwrite this with your own code.
	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");
	input = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(input, 1000, stdin) == NULL;
//	while(!is_null){
	interpret(input);
//		printf("\n");
	print_regs();
//		printf("\n");
//		is_null = fgets(input, 1000, stdin) == NULL;
//	}
//	fgets(input, input_size, stdin);
	printf("Good bye!\n");
	return 0;
}
