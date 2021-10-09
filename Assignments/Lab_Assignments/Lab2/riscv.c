//Alyssandra M. Cordero - LAB2
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
char** instructions; //array of tokens
bool is_done = false;
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
}//END init_regs()!

//check if two strings are equal
bool equals(char* word_1, char* word_2){
	bool is_equal = true;
	while(is_equal && *word_1 != '\0'){
		//An unmatched character found
		if(*word_1 != *word_2)
			is_equal = false;
		++word_1;
		++word_2;
	}
	return is_equal;
}//END equals()!

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

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
//instr is user input string

bool interpret(char* instr){
	int suk;
	bool successful_op = false; 
	instructions = tokenize(instr);//tokenize user input
	if(equals( "ADD", instructions[0])){
		int32_t new_value;
		rd = instructions[1];
		rs1 = instructions[2];
		rs2 = instructions[3];
		rd_int = atoi(rm_first_char(rd));
		rs1_int = (int32_t) atoi(rm_first_char(rs1));
		rs2_int = (int32_t) atoi(rm_first_char(rs2));
		new_value = reg[rs1_int] + reg[rs2_int];
		reg[rd_int] = new_value;//update contents of register
		successful_op = true;
	}//END of ADD!
	
	else if(equals("ADDI", instructions[0])){
		int32_t new_value;

		rd = instructions[1];
		rs1 = instructions[2];
		imm = instructions[3];
		rd_int = atoi(rm_first_char(rd));
		rs1_int = (int32_t) atoi(rm_first_char(rs1));
		imm_int = (int32_t) atoi(rm_first_char(imm)); //MAY BE REGISTER
		printf("rd:  \n%d\n",rd_int);
		printf("rs1:  \n%d\n",rs1_int);
		printf("imm:  \n%d\n",imm_int);

		//perform opperation and save into destination reg
		new_value = reg[rs1_int] + imm_int;
		printf("new value:  \n%d\n",rs1_int);
		reg[rd_int] = new_value;
		successful_op = true;
	}//END OF ADDI!

	else if(equals("LW", instructions[0])){
		printf("I am @lw: \n%s\n");	
		//place holders:
		int new_location;
		int32_t value_in_reg;
		int imm_lw;//OK!
		//necessary variables for the instruction:
		imm = instructions[3];
		rs1_int = (int32_t) atoi(instructions[2]);
		printf("rs1(off-set):  \n%d\n",rs1_int);
		rd = instructions[1];
		//remove unwanted chars 'X' and convert to int:
		rd = rm_first_char(rd);
		imm = rm_first_char(imm);
		//convert values to integer
		rd_int = atoi(rd);
		imm_lw = atoi(imm);
		printf("read number rd :  \n%d\n",rd_int);
		printf("read number imm:  \n%d\n",imm_lw);
		//perform operation
		value_in_reg = reg[imm_lw];
		new_location = value_in_reg + rs1_int; //computing new destination for our value
		printf("new location:  \n%d\n", new_location);
		reg[rd_int] = read_address(new_location, "mem.txt");//saving the value in register
		successful_op = true;//performed a successful operation**
	}//END OF LW!

	else if(equals("SW", instructions[0])){
		printf("I am @sw: \n%s\n");
		int new_location;//memory_address
		int32_t new_value;
		int imm_sw;
		int rd_sw;
		//int32_t value_in_reg;
		rd = instructions[1];
		rs1 = instructions[2];
		imm = instructions[3];

		imm_sw = atoi(rm_first_char(imm));
		rs1_int = (int32_t) atoi(rs1); //its always a constant
		rd_sw = atoi(rm_first_char(rd));

		printf("read number rd :  \n%d\n",rd_sw);
		printf("read number imm :  \n%d\n",imm_sw);
		printf("read number rs1 :  \n%d\n",rs1_int);
		
		new_location = reg[imm_sw] + rs1_int;
		new_value = reg[rd_sw];
		printf("NEW LOCATION :  \n%d\n",new_location);
		printf("NEW VALUE :  \n%d\n",new_value);

		write_address(new_value, new_location, "mem.txt");
		printf("FINISHED! \n%s\n");
		successful_op = true;
	}//END OF SW!
	else{
		is_done = true;
		printf("THAT INSTRUCTION DOES NOT EXISTS\n");//SUCCESSFUL_OP STILL FALSE
	}
	return successful_op;
}

 /* Simple demo program to show the usage of read_address() and write_address() found in memory.c
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
	
	input = malloc(1000 * sizeof(char));//allocate memory for input
	
	bool is_null = false;
	//fgets() returns null if EOF is reached.
		//while(!is_null){
	//	interpret(input);

	//is_null = fgets(input, 1000, stdin) == NULL;
	//}
	//fgets(input, input_size, stdin);
	//bool is_done = false;  
	while(!is_null && !is_done){//while input is NOT NULL
//		printf("HEELLO!\n%s\n", *input);
		//char* eof = "EOF";
		//if(equals(eof, *input)){
	//	//printf("ESTOY EN EOF!");
		//	is_done = true;
		//}else{
		interpret(input);//if instruction exists
		printf("\n");
		print_regs();
		printf("\n");	
		is_null = fgets(input, 1000, stdin) == NULL;
		//}
		//else{
	//	printf("ESTOY EN SIN INPUT\n");
		//}
	}
	printf("Good bye!\n");
	free(input);//free input
	return 0;
}
