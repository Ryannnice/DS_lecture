void printline(int);
void display(void);
void swap(int, int);
int partitionOperation(int, int, int);
void quickSort(int, int);
int main(void);


void printline( int count )
{
   int i ;
	
   for( i = 0 ; i < count ; i++)
   {
      printf("=") ;
   }
	
   printf("\n") ;
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

void swap( int num1 , int num2 )// input index
{
   int temp = intArray[num1] ;
   intArray[num1] = intArray[num2] ;
   intArray[num2] = temp ;
}

// From number with index 'left' and 'right' , the two move from dege to center position.
//               [leftpointer ---->  ......  <----rightpointer]
// until find 'leftpointer' bigger than [pivot] , 'rightpointer' smaller than [pivot]
// SWAP them , then pointers moves on......until they meet each other.
int partitionOperation( int left , int right , int pivot )
{
   int leftPointer = left - 1 ;// to adjust the first step '++leftPointer'
   int rightPointer = right ;

   while(true)
   {
      while( intArray[++leftPointer] < pivot )// this operation straightly find the element bigger than pivot.
      {
         // meditation...( only have ++leftPointer )
      }
      while( rightPointer > 0 && intArray[--rightPointer] > pivot )
      {
         // meditation...
      }

      if( leftPointer >= rightPointer )
      {
         break ;// Finally end at here. Round over
      }
      else// swap
      {
         printf(" item swapped : %d , %d \n", intArray[leftPointer], intArray[rightPointer] ) ;
         swap( leftPointer , rightPointer ) ;
      }
   }
	
   printf(" pivot swapped :%d,%d\n", intArray[leftPointer] , intArray[right] ) ;
   swap( leftPointer , right  ) ;
   printf("Updated Array: ") ;
   display() ;
   return leftPointer ;
}

void quickSort( int left , int right )// intput index : 0 , 20
{
   if( right <= left )
   {
      return ;
   }
   else
   {
      int pivot = intArray[right] ;// pivot : 7
      int partitionPoint = partitionOperation( left , right , pivot ) ;// pivot : intArray[right]
      // recursive algorithm
      quickSort(left,partitionPoint-1) ;
      quickSort(partitionPoint+1,right) ;
   }
}