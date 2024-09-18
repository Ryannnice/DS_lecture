/*
Author: Qinbing Fu
Date: May 2023
Description: Insertion Sort in C Programming
*/

#include <stdio.h>
#include <stdbool.h> 

#define MAX 7

// unsorted integer array
int intArray[MAX] = {5,7,4,3,2,10,8};

// function prototype
void printline(int);
void display(void);
void insertionSort(void);
void main(void);


void printline(int count)
{
   int i;
	
   for(i = 0;i < count-1;i++)
   {
      printf("=");
   }
	
   printf("=\n");
}

void display(void)
{
   int i;
   printf("[");
	
   // navigate through all items
   for(i = 0;i < MAX;i++)
   {
      printf("%d ",intArray[i]);
   }
	
   printf("]\n");
}

void insertionSort(void)
{

   int valueToInsert;
   int holePosition;
   int i;
  
   // loop through all numbers 
   for(i = 1; i < MAX; i++)
   { 
	
      // select originalArray value to be inserted.
      valueToInsert = intArray[i];
		
      // select the hole position where number is to be inserted
      holePosition = i;
		
      // check if previous no. is larger than value to be inserted
      while (holePosition > 0 && intArray[holePosition-1] > valueToInsert)
      {
         intArray[holePosition] = intArray[holePosition-1];
         holePosition--;
         printf("Item moved : %d\n" , intArray[holePosition]);
      }

      if(holePosition != i)
      {
         printf("Item inserted : %d, at position : %d\n" , valueToInsert,holePosition);
         // insert the number at hole position
         intArray[holePosition] = valueToInsert;
      }

      printf("Iteration %d#:",i);
      display();
		printf("\n");
   }
}

void main(void)
{
   printf("Input Array: ");
   display();
   printline(50);
   insertionSort();
   printf("Output Array: ");
   display();
   printline(50);
}

