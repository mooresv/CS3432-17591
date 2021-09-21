#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

//declaring methods
bool delim_character(char c);

bool non_delim_character(char c);

char *word_start(char* str);

char *end_word(char* str);

int count_tokens(char* str);

char *copy_str(char *inStr, short len);

char** tokenize(char* str);

void print_all_tokens(char** tokens,int numbtokens);

void main(){
  printf("Please enter some text: ");
  char a[50];// in relity it will only intake 50-1 characters dues to the \n character(enter)
  char *str = fgets(a,50,stdin);//gets char pointer to base of a string
  int totalCount = count_tokens(str);//get the toal number of tokens
  
  char **p = tokenize(str);//just a temp pointer to not mess with original str
  print_all_tokens(p,totalCount);//doneskies
  
  

  
  
  }




/* Return true (non-zero) if c is a whitespace characer

   ('\t' or ' ').

   Zero terminators are not printable (therefore false) */

bool delim_character(char c){
  if((c == ' ') || (c == '\t') ){
    return true;
  }
  else{
    return false;}
}



/* Return true (non-zero) if c is a non-whitespace

   character (not tab or space).

   Zero terminators are not printable (therefore false) */

bool non_delim_character(char c){
  if((c != ' ') && (c != '\t')){//and because we want to make sure it is neither
    return  true;
  }
  else{
    return false;}
}
/* Returns a pointer to the first character of the next

   space-separated word*/

char *word_start(char* str){
  
  char *tp = str;
  while(delim_character(*tp)){
    if(*tp == '\n' || *tp == '\0'){
      return tp;
    }
    tp++;
  }
  return tp; 


}



/* Returns a pointer to the first space character of the zero

   terminated string*/

char *end_word(char* str){
  char *tp = str;
  while(non_delim_character(*tp)){
    if((*tp == '\n') || (*tp == '\0')){
      return tp;
    }
    tp++;
  }
    return tp;


}

// counts the number of words or tokens

int count_tokens(char* str){
  if((str == NULL) || (*str == '\n')){//the string is empty
    return 0;
  }
  int count = 0;
  char* tp = str;
  char *start = word_start(tp);//assuming there is a word
  char *end = end_word(start);
  
  count++;
  while((*end != '\0') && (*start != '\0') && (*end != '\n') && (*start != '\n')){
    
    start = word_start(end);
    if(*start == '\n' || *start == '\0'){// for cases such as "helo hd  "
      break;                             // this break allows to prevent the count of an extratoken 
    }
    end = end_word(start);//keeps moving for the next word
    count++;
  }
  return count;




}

/* Returns a freshly allocated zero-terminated vector of freshly allocated

   space-separated tokens from zero-term
   For example, tokenize("hello world string") would result in:

     tokens[0] = "hello"

     tokens[1] = "world"

     tokens[2] = "string"

     tokens[3] = 0

*/

char *copy_str(char *inStr, short len){
  char *subStr = (char*)malloc(len * sizeof(char));//allocate memory for substring
  char *s = subStr;
  for(int j = 0;j < len;j++){
    *s= *inStr;
    inStr++;
    s++;
  }
  return subStr;

}



char** tokenize(char* str){
  if((*str == '\n') || (*str == '\0')){
    return NULL;
  }
  int size = count_tokens(str);
  char **allT = (char**)malloc(size * sizeof(char*));//allocate memory for pointers
  char **ptr = allT;
  char *tp = str;// to not mess with original string
  char *s = word_start(tp);
  char *e = end_word(s);
  *ptr = copy_str(s,e-s);
  ptr++;
  while((*s != '\0') && (*s != '\n') && (*e != '\n') && (*e != '\0')){
    
    s = word_start(e);// keeps moving throught the words
    e = end_word(s);
    *ptr = copy_str(s,e-s);
    ptr++;
  }
  return allT;
}





void print_all_tokens(char** tokens,int numbtokens){
  if(numbtokens == 0){// if there is no tokes then there is no ned to keep going
    printf("no tokens available\n");
    return;
  }
  char **ptr1 = tokens;//pointer to tokens array
  char *ptr2 = *ptr1;//pointer to on of the tokens
  for(int i = 0;i < numbtokens;i++){
    printf("Token[%d] = ",i);
    while(*ptr2 != '\0'){
      printf("%c",*ptr2);//prints the token
      ptr2++;
      
    }
    printf("\n");
    ptr1++;//moves onto the next token
    ptr2=*ptr1;
  }
}


