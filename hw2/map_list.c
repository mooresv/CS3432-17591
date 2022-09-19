#include <stdio.h>

#include <stdlib.h>



struct node {

  int value;

  struct node *next;

};



void map(struct node *head, int (*f)(int))

{

  struct node *ptr = head;
  while(ptr != NULL){
    ptr->value = f(ptr->value);
    ptr = ptr->next;
  }

}



int square(int val)

{

  return(val*val);

}



void print_list(struct node *head)

{

  struct node *ptr = head;

  while (ptr != NULL)

    {

      printf("%d ", ptr->value);

      ptr = ptr->next;

    }

  printf("\n");

  return;

}



int main(void) {

  struct node *list, *ptr;

  int i;



  /* create test list with values 9 down to 0 */

  list = (struct node*) malloc(sizeof(struct node));

  list->value = 9;

  list->next = NULL;

  ptr = list;

  for (i = 8; i >= 0; i--) {

    ptr->next = (struct node*) malloc(sizeof(struct node));

    ptr = ptr->next;

    ptr->value = i;

    ptr->next=NULL;

  }



  /* print initial list */

  printf("Initial list: ");

  print_list(list);



  /*  apply map to list with function square */

  map(list, square);



  /* print list after applying map */

  printf("List after applying square map: ");

  print_list(list);



  return 0;

}
