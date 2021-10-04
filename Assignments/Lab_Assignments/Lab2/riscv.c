#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers
char* input; //Array of chars to store user input
int input_size = 40; //size for input
char** instructions; //array of tokens
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
//removes first character of a string or char array
char* rm_first_char(char* original){
	char* string_chopped = original+1;
	return string_chopped;
}
// Iterate through all digits and parse to int.
// value. multiply res by 10 to shuffle digits left.
// For each ASCII character of the digit: subtract the code from '0' to get numerical value.
int myAtoi(char* str)
{
    int res = 0;
    bool sign = false;
	int i = 0;
    if (str[0] == '-') {
        sign = true;
        i++;
    }
 
    for (; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
 
	if(sign){
		return (res * -1); // Return negative result
	}
    return res;
}
//returns true if words are equal. given computarized length using sizeof(x)	
bool compare_char_a(char* word_1, char* word_2, int comp_len){
	int i;
	for(i = 0; i < comp_len; i++){
		if((word_1[i] == NULL)||(word_2[i] == NULL)){
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
	instructions = tokenize(instr);//tokenize user input
	if(instructions[0] == NULL){//checks if the double-array is empty
		return false;
	}
	//if given the lw instruction
	if((compare_char_a(lw, instructions[0], lw_array_size)) == (true) ){ //== REDUNDANT??
		//place holders:
		char* mem_value;
		char* new_location;
		//necessary variables for the instruction:
		imm = instructions[3];
		rs1 = instructions[2];
		rd = instructions[1];
		//remove unwanted chars:
		rd = rm_first_char(rd);
		imm = rm_first_char(imm);
		
		mem_value = read_address(imm, "mem.txt");
		new_location =
		return true;
	}
	//if given the sw instruction
	
	//ADD AND ADDI INSTRUCTION
	//if given the add instruction
	//if given the addi instruction
	return false;
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

	// Below is a sample program to a write-read. Overwrite this with your own code.
	write_read_demo();

	printf("Please enter the RISCV instruction to perform - without parenthesis and each value separated by [ ] example: LW X7 1000 X5 instead of LW X7 1000(X5): \n");//asking user for instruction
	fgets(input, input_size, stdin);
	printf("\n");
	return 0;
}
