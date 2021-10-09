#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h> // malloc & free

#include <stdint.h> // use guaranteed 64-bit integers

#include "tokenizer.h" // Create header file and reference that

#include "memory.h" // built-in functions to read and write to a specific file

#include <string.h>

int32_t* reg; // Array of 32 32-bit registers


void print_regs();
void init_regs();

bool interpret(char* instr);

void write_read_demo();
char** sepImmR1(char* immR1);
int compareStr(char*str1,char*str2);



/**

 * Initialize register array for usage.

 * Malloc space for each 32-bit register then initializes each register to 0.

 * Do not alter this function!

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
int compareStr(char*str1,char*str2){// takes in two string to compare
  char* ptr1 = str1;
  char* ptr2 = str2;
  while(*ptr1 == *ptr2 && (*ptr1 != '\0' || *ptr2 != '\0')){// while equal then we continue
    ptr1++;
    ptr2++;
    

  }
  if(*ptr1 == '\0' && *ptr2 == '\0' ){
    return 1; // the string are equal
  }
  return 0; // at this point the string are not equal
}

void init_regs(){

  int reg_amount = 32;

  reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes

  for(int i = 0; i < 32; i++)

    reg[i] = i;

}
char** sepR1Imm(char* immR1){//separates the lw and sw immedeate and r1
  char* ptr1 = immR1;
  char* ptr2 = immR1;
  int len1 = 0;
  int len = 0;
  while(*ptr1 != '(' && *ptr1 != '\0'){
    len1++;
    ptr1++;
  }
  char* imm = (char*)malloc(len1 * sizeof(char));
  char *immPtr = imm;
  while(*ptr2 != '(' && *ptr2 != '\0'){
    *immPtr = *ptr2;
    immPtr++;
    ptr2++;
    
  }
  ptr1++;// skips (
  
   while(*ptr1 != ')' && *ptr1 != '\0'){
     len++;
     ptr1++;
     
   }
  
   char* register1 = (char*)malloc(len * sizeof(char));
   char *regPtr = register1;
     ptr2++;//skips (
   while(*ptr2 != ')' && *ptr2 != '\0'){
     *regPtr = *ptr2;
     regPtr++;
     ptr2++;
   }
   char **immPreg = (char**)malloc(2 * sizeof(char*));
   char** ptr3 = immPreg;
   *ptr3 = imm;
   ptr3++;
   *ptr3 = register1;
   return immPreg;
}







/**

 * Fill out this function and use it to read interpret user input to execute RV64 instructions.

 * You may expect that a single, properly formatted RISC-V instruction string will be passed

 * as a parameter to this function.

 */

bool interpret(char* instr){
  char *mem_file = "mem.txt";
  // first count the number of tokens
  int countTokens = 0;
  char **tokens =(char**)malloc(4*sizeof(char*));
  char **adder = tokens;
  *adder = strtok(instr," ");
  
  while (*adder != NULL) {
    adder++;
    countTokens++;
    *adder = strtok(NULL, " ");

  }
  
  
 
 
  // now we check for the number of tokens
  // add and addi have 4, lw and sw have 3
  if(countTokens == 3){
    
    char *type = *tokens;
    tokens++;
    char *rdStr = *tokens;
    tokens++;
    rdStr++;//gets rid of the x
    int rdVal = atoi(rdStr);
    char *r1andImmStr = *tokens;
    char** immR1 = sepR1Imm(r1andImmStr);//separates the immideate and register into 2 tokens
    int posNeg = 1;
    char *immStr = *immR1;
    if(*immStr == '-'){//check for a negative offset
      posNeg = -1;
      immStr++;
    }
    int imm = atoi(immStr);
    imm *= posNeg; 
    immR1++;//moves to the r1 token
    char* r1Str = *immR1;
    r1Str++;//removes the X
    int r1Val = atoi(r1Str);
    int32_t address = reg[r1Val] + (2 * imm); 
    // now we check the first token to see if it matches a type of instruction
    
    if(compareStr("LW",type)){
     
    
      reg[rdVal] = read_address(address,mem_file);
      
     
    }
    else if(compareStr("SW",type)){
      int32_t ok = write_address(reg[rdVal],address,mem_file);
      if(ok == (int32_t)NULL){
	return false;
      }
      
    }
    else{
      return false;
    }
   
    return true;
  }
  else if(countTokens == 4){
    // checking for the instruction
    char *type = *tokens;
    tokens++;
    char *rdStr = *tokens;//register that saves value after operation
    tokens++;
    char *r1Str = *tokens;
    tokens++;
    //get rid of the X's
    rdStr++;
    r1Str++;
    int rdVal = atoi(rdStr);
    int r1Val = atoi(r1Str);

    if(compareStr(type,"ADD")){
      //there is another register as the last val in tokens
      char *r2Str = *tokens;
      r2Str++;//get rid of the X
      int r2Val = atoi(r2Str);
      reg[rdVal] = reg[r1Val] + reg[r2Val];
      return true;
    }
    else if(compareStr(type,"ADDI")){
      // the last val in tokens was an immediate
      
      char *immStr = *tokens;
      int posNeg = 1;
      if(*immStr == '-'){
	posNeg = -1;
	immStr++;
      }
  
      int32_t imm = atoi(immStr);
      imm *= posNeg;
      reg[rdVal] = reg[r1Val] + imm;
      return true;
    }
    else if(compareStr(type,"AND")){
      char *r2Str = *tokens;
      r2Str++;
      int r2Val = atoi(r2Str);
      reg[rdVal] = reg[r1Val] & reg[r2Val];
    }
    else if(compareStr(type,"OR")){
      char *r2Str = *tokens;
      r2Str++;
      int r2Val = atoi(r2Str);
      reg[rdVal] = reg[r1Val] | reg[r2Val];
      
    }
    else if(compareStr(type,"XOR")){
      char *r2Str = *tokens;
      r2Str++;
      int r2Val = atoi(r2Str);
      reg[rdVal] = reg[r1Val] ^ reg[r2Val];
      
    }
    else{
      return false;

    }
  }

  return false;
  
  

}





/**

 * Simple demo program to show the usage of read_address() and write_address() found in memory.c

 * Before and after running this program, look at mem.txt to see how the values change.

 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt

 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.

 */

//void write_read_demo(){

  //int32_t data_to_write = 0xFFF; // equal to 4095

  //int32_t address = 0x98; // equal to 152

  //char* mem_file = "mem.txt";



  // Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)

  //int32_t write = write_address(data_to_write, address, mem_file);

  //if(write == (int32_t) NULL)

  //printf("ERROR: Unsucessful write to address %0X\n", 0x40);

  //int32_t read = read_address(address, mem_file);



  //printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned

  //}



/**

 * Your code goes in the main

 *

 */

int main(){

  // Do not write any code between init_regs

  init_regs(); // DO NOT REMOVE THIS LINE



  print_regs();



  // Below is a sample program to a write-read. Overwrite this with your own code.

  //write_read_demo();



  printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");



  char* instruction = malloc(1000 * sizeof(char));

  bool is_null = false;

  // fgets() returns null if EOF is reached.

  is_null = fgets(instruction, 1000, stdin) == NULL;

  while(!is_null){
    if(*instruction == 'e'){
      break;
    }
    interpret(instruction);

    printf("\n");

    print_regs();

    printf("\n");

    fgets(instruction,1000,stdin);

    

  }



  printf("Good bye!\n");



  return 0;

}




