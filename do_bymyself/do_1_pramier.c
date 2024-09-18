#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int length(int arr[])
{  
   int len;
   len = sizeof(arr)/sizeof(arr[0]);/////////////problem here
   return len;
}

void traverse(int arr[])
{
   for (int i = 0; i < 6; i++)
   {
      printf("%d" , arr[i]);
      printf("\n");
   }
   printf("Traverse over\n");
}
void bubbleup(int arr[] , int n )
{
   int  j , temp1 = 0 ;
   bool isswapped = false ;
   //共跑n-1遍
   for(j=0 ; j < n-1 ; j++)
      {
  
         if (arr[j] > arr[j+1])
          {
           temp1=arr[j+1],arr[j+1]=arr[j], arr[j]=temp1; 
           isswapped=true; //当出现任何一次交换，bool就为1，未发生交换（即排序完成时），bool为0，不再递归
          }
      }
  
   if (isswapped ==1 ) 
      bubbleup(arr , n-1);
}

int main()
{
   int arr[6]={3,5,2,66,9,5} ;

   int len;                               //排
   len = sizeof(arr)/sizeof(arr[0]);      //序
   printf("order the array at first:\n"); //数
   bubbleup(arr , len);                   //组
   //遍历 arr[] ：
   traverse(arr);


   printf("the length of arr is %d\n" , len);

}

