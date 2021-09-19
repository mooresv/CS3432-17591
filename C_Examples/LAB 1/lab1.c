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
   int i=0;
   char*pa=NULL;
   
   while(str[i]!='\0'){
      if(delim_character(str[i])){  
         if(str[i+1]='\0')
            pa= &str[i+1];
         break;

      }
      i++;
   }
   return pa;
}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
   
}

// counts the number of words or tokens
int count_tokens(char* str){
   
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
    char* new_string  = (char*) malloc((len+1) * sizeof(char));
    int i;
    for(i=0; i<len; i++){
        new_string[i]= inStr[i];
    }
    new_string[len]= '\0';
    return new_string;
}

char** tokenize(char* str){
   int num_tokens = count_tokens(str);

    char** tokens = (char**)malloc((num_tokens+1) * sizeof(char*));

    int i;

    for(i = 0; i<num_tokens; i++) {
        char* first_letter = word_start(str);
        str= word_terminator(first_letter);
        int length= str - first_letter;
        tokens[i] = copy_str(first_letter, length);

    }

    tokens[i]=NULL;
    return tokens;
}


void print_all_tokens(char** tokens){

   
}

int main() {
	  return (0);
}
