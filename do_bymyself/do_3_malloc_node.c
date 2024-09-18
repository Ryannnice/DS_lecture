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
   NODE *N = (NODE* )malloc( sizeof(NODE) );
   printf("enter the element in this new Node : (intiger)\n");
   scanf("%d" , &e );
   N->elem = e ;
   N->ptr  = NULL ;

   return N ;
}

int main()
{
   NODE * N1 , * N2 , * N3 , * N4 , *N5 ;
   printf("hello! ! ! \n");
   N1->ptr=NULL;      
   printf("hello! ! ! \n");

   N2 = (NODE*)malloc(sizeof(NODE*));//Operation(1) : allocate space to N2 -> Successfully allocate NULL to ptr of N2 !

   N2->ptr=NULL;
   printf("hello! ! ! \n");
   
   N3 = inite(N3) ;                  //Operation(3) : allocate space to N3 (what is different from Operation(1) is--
                                     //             --allocating N3 is reached by Function"inite") -> Successfully allocate NULL to ptr of N3 !
   N3->ptr=NULL;
   printf("hello! ! ! \n");          //Operation(2) : not allocate space to N3 ->  do_2.c crumbled 

                                     //conclusion   : malloc " NODE * " make it certain to allocate value to ptr of N[i] .
   //Magic:
   N1->ptr = N2 ;
   N2->ptr = N3 ;
   N3->ptr = N4 ;
   N4->ptr = N5 ;
   N5->ptr = NULL ;
   
   printf("begining at N1 , ending in N4 , the elem in N5 is : %d\n " , N1->ptr->ptr->ptr->ptr->elem );
}
/*
NODE* inite( NODE *L )
{
   int e ;
   NODE *N = (NODE* )malloc( sizeof(NODE) );
   printf("enter the element in this new Node : (intiger)\n");
   scanf("%d" , &e );
   N->elem = e ;
   N->ptr  = NULL ;

   return N ;
}


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
*/