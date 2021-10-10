#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 32-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers
void init_regs();
bool interpret(char* instr);
void write_read_demo();

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

/*
 * Print registers
 */
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/*
 * Check two strings
 */
bool check_strings(char* string1, char* string2){
	int x = 0;
	int y = 0;
	while(string1[x] != '\0' || string2[y] != '\0'){
		if(string1[x] != string2[y]){ 
      return false;
      }
		if(string1[x] != '\0'){ 
      ++x;
      }
		if(string2[y] != '\0'){
      ++y;
      }

	}
	if(y != x) {
    return false;
    }
	return true;
} 

/*
 * Determine instruction
 */
int get_type(char* instr){
	if(check_strings(instr, "LW")){
   return 0;
  }
	if(check_strings(instr, "SW")){ 
  return 1;
  }
	if(check_strings(instr, "ADD")){
  return 2;
  }
	if(check_strings(instr, "ADDI")){ 
  return 3;
  }
	if(check_strings(instr, "AND")){
   return 4;
  }
	if(check_strings(instr, "OR")){ 
  return 5;
  }
	if(check_strings(instr, "XOR")){ 
  return 6;
  }
	return -1;
}

/*
 * Convert decimal to hex
 */
int32_t to_hex(int decimal){
	char hex[32]; 
	return (int32_t)strtol(hex, NULL, 16);
}

/**
 * Fill out this function and use it to read interpret user input to execute RV32 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
	int num_tokens = count_tokens(instr);
  char** tokens = tokenize(instr);
	int instruction = get_type(tokens[0]);

	switch(instruction){
		//LW memory to reg
		case 0:
		{
			tokens[1]++;//moves the position to read int or String that is an int
			tokens[3]++;	
			int32_t mem_address = atoi(tokens[2]);
			int32_t read_data = read_address(to_hex(mem_address), "mem.txt");
			reg[atoi(tokens[1])] = read_data;
      tokens[1]--;
			tokens[3]--;
			break;
    }
		//SW reg to memory
		case 1:
		{
			tokens[1]++;
			tokens[3]++;	
			int32_t mem_address = atoi(tokens[2]); 
			write_address(reg[atoi(tokens[1])], to_hex(mem_address), "mem.txt");
      tokens[1]--;
			tokens[3]--;
			break;			
		}
		//ADD
		case 2: 
    {
			tokens[1]++;
			tokens[2]++;
			tokens[3]++;			
			reg[atoi(tokens[1])] = reg[atoi(tokens[2])] + reg[atoi(tokens[3])];//changes string to intand adds them and stores it in the reg
      tokens[1]--;
			tokens[2]--;
			tokens[3]--;	
			break;
    }
		//ADDI
		case 3:
    {
			tokens[1]++;
			tokens[2]++;
			reg[atoi(tokens[1])] = reg[atoi(tokens[2])] + atoi(tokens[3]);
      tokens[1]--;
			tokens[2]--;
			break;
    }
		//AND
		case 4:
    {
			tokens[1]++;
			tokens[2]++;
			tokens[3]++;			
			reg[atoi(tokens[1])] = reg[atoi(tokens[2])] + reg[atoi(tokens[3])];
      tokens[1]--;
			tokens[2]--;
			tokens[3]--;	
			break;
    }
		//OR
		case 5:
    {
			tokens[1]++;
			tokens[2]++;
			tokens[3]++;			
			reg[atoi(tokens[1])] = reg[atoi(tokens[2])] + reg[atoi(tokens[3])];
      tokens[1]--;
			tokens[2]--;
			tokens[3]--;	
			break;
    }
		//XOR
		case 6:
    {
			tokens[1]++;
			tokens[2]++;
			tokens[3]++;			
			reg[atoi(tokens[1])] = reg[atoi(tokens[2])] + reg[atoi(tokens[3])];
      tokens[1]--;
			tokens[2]--;
			tokens[3]--;	
			break;
    }
		//Error
		case -1:{
			printf("Did not enter a correct instruction");
			break;
    }
	}
//print tokens
	printf("\n");
	for(int i = 0; i < num_tokens; ++i){
		printf("Token [%d]: %s\n", i, tokens[i]);
	}
  return 0;
}

/**
 * Your code goes in the main
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();

	printf("\n");
	printf("RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nPress 'EOF' (Ctrl+d) character to end program\n");

	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		interpret(instruction);
		print_regs();
		printf("\n");
    printf("Type RV32 another instructions or press 'EOF' (Ctrl+d) character to end program");
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}

