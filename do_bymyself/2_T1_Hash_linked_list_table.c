#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash( unsigned int n )
{
    return n % 10 ;
}

unsigned int hash_pro_max_ultra_ultimate( unsigned int n )
{
    return (int)(sqrt(n%1000+n*n%100+n*n%10)) % 10 ;
}

typedef struct linked_list_node
{
    int data ;
    struct linked_list_node* next ;
}node ;

// initailize a node
node* create( int num )
{
    node* temp = (node*)malloc(sizeof(node ) ) ;
    temp->data = num ;
    temp->next = NULL ;
    return temp ;
}

// find tail of the linked_list
node* findTargetPosition(node* target)
{
    if (target == NULL){
        return NULL ;
    }else{  
        node* temp = target ;

        while (temp->next != NULL){
            temp = temp->next;
        }

        return temp;
    }
}

void main()
{
    int arr[15] =
  { 534, 415, 465, 459, 869, 
    442, 840, 180, 450, 265,
    23 , 946, 657,  3 , 29  };

    // initialize table : 
    node* linked_table[10] ;
    for( int i = 0 ; i < 10 ; i++ )
    {
        linked_table[i] = NULL;
    }

    // payload : 
    printf("\n\nPayload : \n\n") ;
    for( int i = 0 ; i < 15 ; i++ )
    {
        node* target = linked_table[ hash(arr[i]) ];
    
        if (target == NULL){
            linked_table[ hash(arr[i]) ] = create(arr[i]);
        }else{
            node* last_node = findTargetPosition(target);
            last_node->next = create(arr[i]);
        }
    
        printf("'%d' inserted successfully\n", arr[i]);
    }

    // traversal : 
    printf("\n\nTraversal : \n\n") ;
    for (int i = 0; i < 10; i++)
    {
        node* current = linked_table[i];
        printf("Element in '%d' index : ", i);
        
        while (current != NULL)
        {
            printf("%d", current->data);
            if(current->next) printf(" -> ") ;
            current = current->next;
        }
        printf("\n") ;
    }



    printf("\n\nDemostration over...\n ") ;
}