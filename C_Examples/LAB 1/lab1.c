#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c){
   return c==' '||c=='\t'; 
 
}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c){
   if(c==' ' || c=='\t' || c=='\0')
    return 0;
   return 1;
   
}

/* Returns a pointer to the first character of the next
   space-separated word*/
char *word_start(char* str){
    while(delim_character(*str)){  //until there are whitespaces keep moving
          str++;
	  
	}
    return str;


   
}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
    
    while(non_delim_character(*str)){ //until there are non-whitespaces keep moving
        str++;
    }
    return str;
   
}

// counts the number of words or tokens
int count_tokens(char* str){
    int ctr = 0; //counter
    while(*str != '\0'){ //keep iterating while we are not in the end of string
        while(delim_character(*str)){  
            str++; //until there are white spaces keep moving
        }
        
        if(non_delim_character(*str)){
            ctr++; //increase counter when letter is founded
        }
        
        while(non_delim_character(*str)){ //until there are non-white spaces keep moving
            str++; 
        }
    }
    
    return ctr;
   
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char *copy_str(char *inStr, short len){
    char* new_string  = (char*) malloc((len+1) * sizeof(char)); //allocate memory for the new string
    int i; 
    for(i=0; i<len; i++){
        new_string[i]= inStr[i];
    }
    new_string[len]= '\0'; //last element as zero terminator
    return new_string;
}

char** tokenize(char* str){
   int num_tokens = count_tokens(str);

    char** tokens = (char**)malloc((num_tokens+1) * sizeof(char*)); //allocate memory for the new string

    int i;

    for(i = 0; i<num_tokens; i++) {
        char* first_letter = word_start(str);
        str= end_word(first_letter);
        int length= str - first_letter;
        //printf("LENGTH: %d", length); //<-- check length of each letter
        tokens[i] = copy_str(first_letter, length);

    }

    tokens[i]=NULL; 
    
    return tokens;
}


void print_all_tokens(char** tokens){
    printf("\n");
    int i;
    for(i = 0; tokens[i] != NULL; i++){

      printf("Tokens [%d]: %s\n", i, tokens[i]); 

    }
    
   
}

int main() {

    char words[500];
    printf("Enter your input: \n");
    printf("$");
    //read input from the standard input stream and
    //store into string pointer
    fgets(words, 500, stdin); 

    char**tokens= tokenize(words); 
    print_all_tokens(tokens);
    return(0);
}



