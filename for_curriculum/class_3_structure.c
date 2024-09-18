/*
This exemplifies the use of struct data type.
*/

#include <stdio.h>
#include <stdlib.h>

struct point           //define "(x , y)" to discribe a dot
{
    int x;
    int y;
};

struct abc
{
    int a;
    char b;
    char c;
};

// attention: self referential structures
struct self
{
    int p;
    struct self *ptr;               //this pointer can point at another structure which is the same as it self 
};
struct code
{
    int i;
    char c;
   struct code *ptr;                //maybe an exact example of the upper structure
};

struct point edit(struct point p)   // mached founction of upper structure
{
    (p.x)++;                        // this operation is based on numerical value that have been "copied"  but not the "pointed value"
    p.y = p.y + 5;
    return p;                       //  as a resule , only "return" can make it feasible to apply the operation based on "copid" value.
}                                   //  Importanlty , if i do not use a pointer to pass the value and at the same time forgot to "return" ,
                                    //  the opreation can only excute in the founction , making no difference to the real value outer.

void print(struct point p)
{
    printf("%d %d\n", p.x, p.y);    //  analysis is the same as upper founction "EDIT"
}

void print2(struct point *ptr)
{
    printf("%d %d\n", ptr->x, ptr->y);   //passing the pointer of current structure , making it easier to realize large-scale operation.
}

void print3(struct abc arr[], int arr_size)  // passing a structure by copying . not Efficient .
{
    int i;
    for(i=0; i<arr_size; i++)
    {
        printf("%d %c %c\n", arr[i].a, arr[i].b, arr[i].c);  //assign value to variable . !!Each "arr" has 3 elements.
    }
}

void edit2(struct point p)
{
    (p.x)++;
    (p.y)+=5;                                // no pointer -> virtual operation -> meaningless calculation in the function.
}                                            // the real value won't change anyhow.

struct point* func(int a, int b)             //Structure pointer. 
{
    struct point *ptr = (struct point*)malloc(sizeof(struct point)); //allocate enough storage to the value entered.
    ptr->x = a;                                    //pointer operation , efficient.
    ptr->y = b + 10;
    return ptr;                                    // return a pointer which points to the begining of the struccture.
}

int main()                                        // main , eventually. 
{
    // 1
    struct point p1 = {23, 45};
    struct point p2 = {56, 90};
    //p1 = edit(p1);
    //p2 = edit(p2);
    edit2(p1);
    edit2(p2);
    print(p1);
    print(p2);
    printf("integer size: %d bytes\n", sizeof(int));
    printf("struct point size %d bytes\n", sizeof(struct point));  //sizeof.  uesd outside of the founction.

    // 2
    struct point *ptr1,*ptr2;    //pointer.
    ptr1=func(2,3);              //"func" , appear at line 67  which returns a pointer , making it rational to assign value to "ptr1(a pointer)".
    ptr2=func(6,9);
    print2(ptr1);
    print2(ptr2);
    free(ptr1);
    free(ptr2);
    ptr1=NULL;
    ptr2=NULL;                   //good habit. avoid wild pointer.

    // 3
    struct abc arr[2]={{1,'A','a'}, {2,'B','b'}};  //1 , num or asco , 'A' , char .
    print3(arr, 2);

    // 4
    struct code var1;
    var1.i=66;
    var1.c='B';
    var1.ptr=NULL;            //assignment.
    struct code var2;
    var2.i=67;
    var2.c='C';
    var2.ptr=NULL;            //NULL as initialization.

    // magic
    var1.ptr=&var2;           //contact two structure of a kind. pointer inside the first structure points to the second structure.
    printf("%d %c\n", var1.ptr->i, var1.ptr->c);    //utimately points to the element of the second structure.

    return 0;
}