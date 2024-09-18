/*
Author: Qinbing Fu
Date: May 2023
Description: Bubble Sort in C Programming
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX 10

// unsorted integer array
int list[MAX] = {1,8,4,6,0,3,5,2,7,9};

// function prototype
void display(void);
void bubbleSort(void);
void main(void);


void display(void)
{
   int i;
   printf("[");
	
   // navigate through all items
   for(i = 0; i < MAX; i++)
   {
      printf("%d ",list[i]);
   }
	
   printf("]\n");
}

void bubbleSort(void)
{
   int temp;
   int i,j;
	
   bool swapped = false;
   
   // loop through all numbers
   for(i = 0; i < MAX-1; i++)
   { 
      swapped = false;
		
      // loop through ahead numbers
      for(j = 0; j < MAX-1-i; j++)
      {
         printf("Items compared: [ %d, %d ] ", list[j],list[j+1]);

         // compare the numbers
         // swap the numbers
         // Bubble up the largest number
			
         if(list[j] > list[j+1])
         {
            temp = list[j];
            list[j] = list[j+1];
            list[j+1] = temp;

            swapped = true;
            printf(" => swapped [%d, %d]\n",list[j],list[j+1]);
         }
         else
         {
            printf(" => not swapped\n");
         }
      }

      // if no numbers were swapped 
      // array is sorted now, break the loop. 
      if(!swapped)
      {
         break;
      }
      
      printf("Iteration %d#: ",(i+1));
      display();
   }
	
}

void main(void)
{
   printf("Input Array: ");
   display();
   printf("\n");
	
   bubbleSort();
   printf("\nOutput Array: ");
   display();
}
