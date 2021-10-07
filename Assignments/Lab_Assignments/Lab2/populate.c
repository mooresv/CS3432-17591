#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_32bit 4294967295; // 32 bits of all 1s
#define SEED 3432

char* memory_str(int32_t address, int32_t data);
void populate(int32_t max_dwords, char* file);

int main(){
	srand(SEED); // Set the rand() seed
	populate(100, "mem.txt"); // Add 100 lines of random data to mem.txt
}

// Constructs the memory line string and adds it at the appropriate address in mem.txt
char* memory_str(int32_t address, int32_t data){
	char* line_str = malloc(22 * sizeof(char));
	// line_str: "0x"
	line_str[0] = '0';
	line_str[1] = 'x';
	line_str[20] = '\0';

	// line_str: "0x00000008"
	char addr_str[9];
	// take the address int32_t convert it to a hex string with leading up to 8 leading zeroes
	sprintf(addr_str, "%08X", address);
	strcpy((char*) &(line_str[2]), addr_str);

	// line_str: "0x00000008: "
	line_str[10] = ':';
	line_str[11] = ' ';

	char upper_str[9];
	int32_t upper_word = data;


	// line_str: "0x00000008: FFFFFFFF"
	sprintf(upper_str, "%08X", upper_word);
	strcpy(&line_str[12], upper_str);


	return line_str;
}


// Iteratively add random 32-bit ints until max_words words are added
void populate(int32_t max_words, char* file){
	FILE* mem_file = fopen(file, "w");

	/* fopen() return NULL if unable to open file in given mode. */
   	 if (mem_file == NULL){
		/* Unable to open file hence exit */
		printf("\nUnable to open file.\n");
		printf("Please check whether file exists and you have read/write privilege.\n");
		return;
    	}

    	for(int32_t i = 0; i < max_words; i++){
    		// creates 1 random 32-bit int a
    		int32_t data = ((int32_t)rand());

    		char* mem_str = memory_str(i*2, data);
    		fputs(strcat(mem_str,"\n"), mem_file);
    	}

    	fclose(mem_file);
}
