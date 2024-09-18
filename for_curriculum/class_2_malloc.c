//  动态内存分配  Dynamic memory allocation (DMA)  <-->  Static.....
#include <stdio.h>
#include <stdlib.h>
int main ()
{
   int* p = NULL ;
   int n =0 ;
   p = (int *) malloc(sizeof(int) );

   if (p == NULL )
   {
    printf("ERROR \n") ;
    exit(1) ;
   }

   printf(" enter number that u need to memory : \n");
   
   scanf("%d" , p );

   printf("%d \n" , *p) ;

   printf(" enter number that u need to memory : \n");

   p = (int *) realloc (p , sizeof(int) ) ; 
   
   if (p == NULL )
   {
    printf("ERROR \n") ;
    exit(1) ;
   }

   
   scanf("%d" , p+1 );

   printf("%d , %d \n" , *p , *(p+1) ) ;

   free(p) ;
  
   printf("%d , %d " , *p , *(p+1) ) ;
}