#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct nodeoflinking
{
   int elem ;
   struct nodeoflinking* ptr ;
}NODE;

NODE* inite( NODE *L )
{
   int e ;
   
   printf("enter the element in this new Node : (intiger)\n");
   scanf("%d" , &e );
   L->elem = e ;
   L->ptr  = NULL ;

   return L ;
}
int main()
{
   NODE * N1 , * N2 , * N3 , * N4 , *N5 ;
   
   N1 = (NODE* )malloc( sizeof(NODE) );
   N2 = (NODE* )malloc( sizeof(NODE) );
   N3 = (NODE* )malloc( sizeof(NODE) );
   N4 = (NODE* )malloc( sizeof(NODE) );
   N5 = (NODE* )malloc( sizeof(NODE) );
   N1->ptr=NULL;        
   N2->ptr=NULL;
   N3->ptr=NULL;
   N4->ptr=NULL;
   N5->ptr=NULL;

   N1 = inite(N1) ;
   printf("the elem in N1 is :%d\n" , N1->elem );
   
   N2 = inite(N2) ;
   printf("the elem in N2 is :%d\n" , N2->elem );
   
   N3 = inite(N3) ;
   printf("the elem in N3 is :%d\n" , N3->elem );
   
   N4 = inite(N4) ;
   printf("the elem in N4s is :%d\n" , N4->elem );
   
   N5 = inite(N5) ;
   printf("the elem in N5 is :%d\n" , N5->elem );
   ////////////////////////////////////Magic :
   N1->ptr = N2 ;
   N2->ptr = N3 ;
   N3->ptr = N4 ;
   N4->ptr = N5 ;
   N5->ptr = NULL ;
   
   printf("begining at N1 , ending in N4 , the elem in N5 is : %d\n " , N1->ptr->ptr->ptr->ptr->elem );
}