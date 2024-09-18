//  指针
#include <stdio.h>
#include <stdlib.h>
int main ()                    //// 1 未分配指针的地址时，要初始化为NULL
{                              //// 2 dereferencing指针前判断指针是否为NULL
 
   int a=10 ;
   void *p = &a ;
   
   printf("%d" , *(int *)p);   // 空指针类型转换为int
   printf("\n");

   int *ptr =NULL;             //空指针 未分配指针的地址时，要初始化为NULL  
   ptr = (int *)malloc(100*sizeof(int));   //malloc
   free(ptr);                  //free用过的内存
   
   ptr=NULL;//防止指针悬挂(指针指向已经free的地址)!!!!


   printf("%d" , sizeof(NULL));

   return 0;
}

/*   指针：基本
#include <stdio.h>
#include <stdlib.h>
int main()
{
   void* p;
   char a=10;
   p=  &a;
   printf("%d" , *(char*)p );
}*/
