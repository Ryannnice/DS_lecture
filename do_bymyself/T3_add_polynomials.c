
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
   int val;
   int exp;
   struct node* next;
}node;

void insertFirst(node** head, int val, int exp)
{
   // new node*
   node* neww = (node*) malloc(sizeof(struct node));

   if(neww == NULL){
      printf("malloc wrong ! \n");
      return ;
   }

   neww->val = val;
   neww->exp = exp;
   neww->next = *head;
   *head = neww;
}

void traverse(node* head)
{
   // reset to the first node* instead of the "header".
   node* ptr = head ;

   // print as : [  (....)+(....)+(....)+(....)+ ... ]
   printf("\n[ ");
   
   while(ptr != NULL) 
   {

      if(ptr->val > 0 )
      printf("(%d*X^%d)" , ptr->val , ptr->exp );
      else if(ptr->val < 0 )
      printf("((%d)*X^%d)" , ptr->val , ptr->exp );
      // case coefficient == 0 :
      else 
      {}
      // Judge --> find the right place to add " + "
      if(ptr->next && ptr->val != 0 )  printf("+");

      // go on
      ptr = ptr->next;

   }
   // over
   printf(" ]");
}

node* add(node* A, node* B)
{
   node* neww = NULL;
   node* ptr1 = A;  // Known the adress of pointer "A" , then easily can know the content of "A",
                    // which is the adress of content in pointer "A" .
   node* ptr2 = B;

   while(ptr1 && ptr2 )
   {
      if(ptr1->exp == ptr2->exp)
      {
         insertFirst(&neww,ptr1->val+ptr2->val,ptr1->exp);
         ptr1 = ptr1->next;
         ptr2 = ptr2->next;
      }
      else if(ptr1->exp > ptr2->exp)
      {
         insertFirst(&neww,ptr1->val,ptr1->exp);
         ptr1 = ptr1->next;
      }
      else
      {
         insertFirst(&neww,ptr2->val,ptr2->exp);
         ptr2 = ptr2->next;
      }
   }

   while(ptr1)
   {
      insertFirst(&neww,ptr1->val,ptr1->exp);
      ptr1 = ptr1->next;
   }

   while(ptr2)
   {
      insertFirst(&neww,ptr2->val,ptr2->exp);
      ptr2 = ptr2->next;
   }
   return neww;
}
int main()
{
   node* A , *B , *C , *result ;
   A = NULL;
   B = NULL;
   C = NULL;
   result = NULL;


   insertFirst(&A,5,1);// &A : the adress of pointer "A".
   insertFirst(&A,4,2);
   insertFirst(&A,3,3);
   insertFirst(&A,2,4);
   insertFirst(&A,1,5);
  
   traverse(A);
   printf("\ninit A over \n");

   insertFirst(&B,-50,1);
   insertFirst(&B,4,2);
   insertFirst(&B,0,3);
   insertFirst(&B,0,4);
   insertFirst(&B,-3,5);

   traverse(B);
   printf("\ninit B over \n");
   
   C = add(A , B);
   traverse(C);

   result = add(C , A);
   traverse(result);

   free(A);
   free(B);
   free(C);
   free(result);
   
   //only be able to add two decending order polynomials.....
   //need a founction to combine the similar items..
}