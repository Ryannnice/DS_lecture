/*
Author: Qinbing Fu
This introduces stack operations in C programming.
*/

#include <stdio.h>
#include <stdlib.h>

int stack[8]; //( -> MAXSIZE -> upgrade by "MAXSIZE". ) <-- WRONG way.
int *ptr_stack = &stack[0] ; //position of old stack
int *ptr_new = NULL ;

int MAXSIZE = 8 ; 
int top = -1; 

int isempty()
{

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull()
{

   if(top == MAXSIZE - 1)
      return 1;
   else
      return 0;
}

int peek()
{
   return stack[top];
}

int pop()
{
   int data;
	
   if(!isempty())
   {
      data = ptr_stack[top--];
      //top = top - 1;
      printf("Poping data: %d\n", data);
      return data;
   } 
   else
   {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}
int* increase_length( int* target_stack )
{
   int* new_stack = (int*)malloc( (2*MAXSIZE) * sizeof(int));
   
   for(int i = 0 ; i < MAXSIZE ; i++ )
   {
      new_stack[i] = stack[i] ;
     // printf("%d  " , new_stack[i]);
   }
   
   MAXSIZE *= 2 ;
   return new_stack ;
}
void push(int data)
{

   if(!isfull())
   {
      top = top + 1;
      stack[top] = data;
      printf("Pushing data: %d\n", data);
   } 
   else
   {
      printf("Could not insert data, Stack is full.\n");
      
      //homework:
      //increase size of stack
      
      ptr_new = increase_length(ptr_stack);

      top = top + 1;
      ptr_new[top] = data;
      printf("Pushing data: %d\n", ptr_new[top] );
      printf("Stack has been increased ! \n");
   }
}

void traverse(int* p)
{

   for(int i = 0 ; i < top+1 ; i ++ )
   {
      printf("%d\t" , p[i]);
   }
   printf("\n");
}

int main() {
   // push items on to the stack 

   for(int i = 0 ; i < 30 ; i++)
   {
      push(i);
   }
   
   
   printf("Stack full: %s\n", isfull()?"true":"false");
   printf("Stack empty: %s\n", isempty()?"true":"false");

   printf("Element at top of the stack: %d\n" ,peek());

   // print stack data 
   while(!isempty()) {
      int data = pop();
      //printf("%d\n",data);
   }

   printf("Stack full: %s\n", isfull()?"true":"false");
   printf("Stack empty: %s\n", isempty()?"true":"false");
   
   //traverse(ptr_stack) ;
   return 0;
}

