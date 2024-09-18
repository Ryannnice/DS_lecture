//My problem exists at line 37.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
#define INCREMENT 10

typedef struct                          //i want a linear table: length and listsize are certain nums , but the content is pointered(*element)
{
    int *element;                       //this struct is a table but not a NODE, containing "element[0]" , "element[1]" , 'element[2]" .......
    int length;
    int listsize;
}list;

void InitList(list *L)                  //initialization
{
    L->length = 0 ;

    L->element = (int *)malloc( MAX * sizeof(int));
    if(L->element==NULL)
    {
       printf("error when allocating !");
       return; 
    }
    else

    L->listsize = MAX;
    int i = 0;
    printf("Enter the length of sqlist that u need :\n");
	   scanf("%d",&L->length);
	printf("Enter %d elements one by one :\n",L->length); 

	for(i=0 ; i < L->length ; i++)
    {
    
	   scanf("%d",&L->element[i]);     //i felt ambiguous before...and used "element[i]"
    }                                   //now i wonder why a pointer named "element" could be devided into "element[0]","element[1]"......??? 
    printf("List setting is over.\n\n");
}
void IsEmpty(list *L)
{
    if(L->length==0)
    printf("This is an empty List\n");
    else
    printf("Not empty\n");
}
void Traverse(list *L)
{   
    if(L->length==0)
    printf("This is an empty sqlist.\n");
    else
    printf("elements in this sqlist are :\n");
    for(int i=0 ; i < L->length ; i++)
    printf("%d \n" , L->element[i]);
}
int Length(list *L)
{
    return L->length;
}
void Locate(list *L )
{
    int e;
    printf("Enter the element u want to Locate :\n");
    scanf("%d" , &e);
    int n , flag=0;
    for ( n = 0; n < L->length; n++)
    {

        if(L->element[n] == e)
        {
        printf("Found ! element %d is at location No.%d \n" , e , n+1);
        flag++;
        }
    }
    if (flag==0)
    {
        printf("No correct elements here.\n");
    }
    else
        printf("Totally %d wantted elements here.\n" , flag);
    
}
int Location(list *L , int wanttednum)    //返回表里所需数字的位置坐标(只第一个)。
{
    int n , location =-1 , e = wanttednum ;
    for ( n = 0; n < L->length; n++)
    {
        if(L->element[n] == e)
        {
        location = n+1 ;
        }
    }
    return location ;
}
void Insert( list *L , int i , int e)    //在第 i 个元素前插入 =元素 e ，表长变长 ，无返回值。
{
        int length = L->length;       //length 用作计数，计算发生交换的次数。
        int swapnum = L->length;      //swapnum  用作记录 将被交换的数的所在位置。起始值为列表的最后一项的后一项（空）。
    if(1 <= i && i <= L->length +1 )
    {
        L->listsize += INCREMENT ;    //增加表长
        
        for ( int j = 0 ; j < (length - i +1) ; j ++ )
        {
        L->element[swapnum] = L->element[swapnum - 1];
        --swapnum;
        }
        
        L->element[i - 1] = e ;       //全体后移完成 ， 空位置留给所插入元素。
        
        printf("Insert over ! \n");
    }
    else if(i > L->length +1 )
    {
        printf("List is too short , new element was Inserted at the tail .");
        L->listsize += INCREMENT ;
        L->element[length] = e ;
    }
    else
        printf("Error insert position !!");
}


int main()
{  
    list *A;                     //*A 是结构体指针 ， 所以可以直接把A传入需求参数为指针的函数里。

    InitList(A);

    IsEmpty(A);
    
    Traverse(A);
printf("\n");
    Locate(A);
printf("\n");
    int a = Location(A , 4) ;
printf("Location of the Number 4 wantted at Founction Location is %d \n" , a);    
    

    printf("%d" , A->element[0] );
     printf("\n");
    printf("%d" , A->element[1] );
     printf("\n");
    printf("%d" , A->element[2] );
     printf("\n");
    printf("%d" , A->element[3] );

    printf("\n");
    Insert(A , 2 , 1008611);           //trying to insert "1008611"
    
    printf("%d" , A->element[0] );
     printf("\n");
    printf("%d" , A->element[1] );
     printf("\n");
    printf("%d" , A->element[2] );
     printf("\n");
    printf("%d" , A->element[3] );
     printf("\n");
    printf("%d" , A->element[4] );

}