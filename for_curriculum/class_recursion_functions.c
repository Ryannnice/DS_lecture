/*
Author: Qinbing Fu
Date: 2023 Apr
This introduces simple implementations of recursion functions in C programming.
*/

#include <stdio.h>
#include <stdlib.h>

// a function calling itself
void function(int value) 
{
   if(value < 1)
      return;
   function(value - 1);

   printf("%d ",value);   
}

// a function that calls another function which in turn calls it again
void function1(int value1) 
{
   if(value1 < 1)
      return;
   function2(value1 - 1);
   printf("%d ",value1);   
}
void function2(int value2) 
{
   function1(value2);
}

int main()
{
   printf("A function calls itself: \n");
   function(10);
   printf("\n\n");

   printf("Two functions call each other: \n");
   function1(50); // understood
   printf("\n");
   printf("Two functions call each other: \n");
   function2(50); // understood
   printf("\n\n");

   return 0;
}

