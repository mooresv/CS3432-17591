/*Alyssandra M. Cordero*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
char* arr; /*this is the pointer for the user input/dynamically alocated array.*/
size_t arrSize = 40; //size of the array 
char** tokens;//Array of tokens for tokenize function

/*tokenizer implementation*/

/* Return true (non-zero) if c is a whitespace characer
 * ('\t' or ' ').
 * Zero terminators are not printable (therefore false) */
bool delim_character(char c){
	if(c == '\t' || c == ' '){
		return true;
	}
	return false;
}

/* Return true (non-zero) if c is a non-whitespace
 * character (not tab or space).
 * Zero terminators are not printable (therefore false) */
bool non_delim_character(char c){
	if(c != '\t' && c != ' '){
		return true;
	}
	return false;
}

/* Returns a pointer to the start of the word*/
char* word_start(char* str){
	int i = 0;
	while(delim_character(str[i]) == true){
		if(str[i] =='\0')
			return NULL;
		i++;
	}
	return &str[i]; //to return the pointer to start - specified & for return
}

/* Returns a pointer to the end of the word*/
char* end_word(char* str){
	str = word_start(str);
	int i = 0;
	while(non_delim_character(str[i]) == true){
		if(str[i] == '\0')
			return &str[i-1];
		i++;
			}
return &str[i];
}

// counts the number of words or tokens
int count_tokens(char* str){
int n = 0, i = 0;
while(str[i] != '\0'){//while the paragraph is not over
	if(str[i] == ' '){
	n++;
	}
	i++;
}
n++;//for the last word
return n;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
 * space-separated tokens from zero-terminated str.
 *  For example, tokenize("hello world string") would result in:
 */
char *copy_str(char *inStr, short len){
	char *outStr = malloc((len) * sizeof(char));
	int i = 0;
	while (i < len){
	outStr[i] = inStr[i]; // cp contents into new array
	i++;
	}
	outStr[i] = '\0';
	return outStr;
}
/*The tokenize function creates the array of words/tokens*/
char** tokenize(char* str){
	int i = 0;
	int num_of_tokens = count_tokens(str);

	char** tokens = malloc(num_of_tokens * sizeof(char*));//array initialization
	char* k = str; //start and end pointers to iterate through original string of chars
	char* j = str;	
	
	while(i < num_of_tokens){
	k = word_start(j);        //set pointers - first pointer (k) to beginning of word
	j = end_word(k);          //second pointer to the end of recently discovered word
	tokens[i] = copy_str(k, j - k); //saves the word into array
	i++;
	}
	tokens[i] = NULL;//delimiter for end of tokens[]
	return tokens;
}
/* Function that prints all the tokens from an array of words*/
void print_all_tokens(char** tokens){
	int i = 0;
	while(tokens[i] != NULL){
		printf("%s\n",tokens[i]);
		tokens++;
	}
}

/*main method*/
//int main(){
//arr = (char*) malloc(arrSize * sizeof(char));//declaring the array with the declared size
//printf("Please enter your text (40 char max. ): \n");
//fgets(arr, arrSize, stdin);
//printf("\n");

//token functionality
//printf("Output: \n");

//print_all_tokens(tokenize(arr));

//free allocated memory
//free(arr);
//free(tokens);
//return 0;

//}//end of main()
