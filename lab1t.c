#include <stdlib.h> //malloc()
#include <stdio.h> //fgets
#include <stdbool.h> //true & false
#define x 100 //String
 
/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c) {
 if((c == ' ' || c == '\t') && c != '\0') {
 return true;
 }
 return false;
 
}
 
/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */ 
bool non_delim_character(char c){
 if((c != ' ' && c != '\t') && c != '\0') {
 return true;
 }
 return false;
}
 
/* Returns a pointer to the first character of the next
   space-separated word*/
char *word_start(char *str){
 int n = 0;
 while(delim_character(str[n])) {
 n++;
 }
 return &str[n];
}
 
/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char *str) {
 str = word_start(str);
 int n =0;
 while(non_delim_character(str[n])){
 n++;
 }
 return &str[n];
}

// counts the number of words or tokens
int count_tokens(char *str) {
 int acc;
 for(acc = 0; str != end_word(str); acc++) {
 str = end_word(str);
 }
 return acc;
}
 
/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char *copy_str(char *inStr, short len) {
 int n;
 char *copy = (char *)malloc(sizeof(char) * (len+1)); 
 for(n=0; n< len; n++) {
 copy[n] = inStr[n]; 
 }
 copy[n] = '\0'; 
 return copy;
}

char **tokenize(char *str) {
 
 int n;
 int tokens = count_tokens(str);
 char **array = malloc(sizeof(char *) * (tokens)); 
 char *start = word_start(str);
 char *end = end_word(str); 
 
 for (n = 0; n < tokens; n++) {
 array[n] = copy_str(start, end-start); 
 start = word_start(end); 
 end = end_word(start); 
 }
 
 array[n] = 0;
 return array;
}
 
void print_all_tokens(char** tokens){
 int n = 0;
 while(tokens[n]) {
 printf("Tokens %d: = %s\n", n, tokens[n]);
 n++;
 }
 return;
}
 
int main() {
 char inStr[x]; 

 printf("Please enter the input string: \n");
 fgets(inStr, x, stdin);
 
 char** tokens = tokenize(inStr);
 print_all_tokens(tokens);

 return 0;
}