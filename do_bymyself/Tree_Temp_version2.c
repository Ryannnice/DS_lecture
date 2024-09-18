/*
    Version 2.0
    Wellcome to My Procedure which shows rudimentary operation of TREE DATA STRUCTURE
    Author : Renyavn Liu
    Time : April , 2023 .

    Updated in version 2.0 :
    1. line 128 , 134 , 135 recorrect inserting operation.
    2. structure changed : add "next" node at "struct tree_node" --> cancle "struct linking_node"
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree_node{
    int element ;
    struct tree_node* parent ; // points to parent node of this tree_node.
    
    struct tree_node* head ; // points to first son node
    struct tree_node* tail ; // points to last son node

    struct tree_node* next ; // points to brother node
    int node_count ;
}tree_node ;

// Traverse---------Using recursion 
void traverse( tree_node* target_node )
{
    printf( "%d\t" , target_node->element ) ;
    linking_node* temp = target_node->head ;
    
    while(temp)
    {
        traverse(temp->node) ;
        temp = temp->next ;
    }
}

// this Founction will add a children node for target node:  (baasic founction)
tree_node* increase_node(tree_node* target_node , int data ) // data will be assign to value in children node of "node".
{
    linking_node* new_link_node = (linking_node* )malloc( sizeof(linking_node) ) ;
    tree_node* new_tree_node = (tree_node* )malloc( sizeof(tree_node) ) ; // malloc for two new nodes.
 
    new_tree_node->element = data ;
    new_tree_node->parent = target_node ;
    new_tree_node->head = NULL ;
    new_tree_node->tail = NULL ;
    new_tree_node->node_count = 0 ; // initialize new tree_node.

    new_link_node->node = new_tree_node ; // core operation
    new_link_node->next = NULL ; // initialize new link_node.
    
    if (!(target_node->head)) {
        target_node->head = new_link_node;
    } else {
        target_node->tail->next = new_link_node;
    }
    target_node->tail = new_link_node;
    target_node->node_count++; // operation at target_node.

    return new_tree_node ;
}

// the number of children_node of target_node:
int children_nums( tree_node* target_node )
{
    return target_node->node_count ;
}

// whether node is leaf or not :
bool is_leaf( tree_node* target_node )
{
    if(target_node->head) return 0 ;
    return 1 ;
}

// whether tree is absolutely emmpty......
bool is_empty( tree_node* target_node )
{
    return ( target_node->parent == NULL && target_node->head == NULL && !(target_node->element) ) ;
}

bool has_brother( tree_node* target_node )
{
    if(target_node->parent->node_count >= 2) return 1 ;

    return 0 ;
}

// detach a son_tree :  -cut off- between father and son node
// this founction cut the son node whose element is what you are searching for.
void detach( tree_node* father , int target_element_of_son )
{
    linking_node* temp = father->head ;

    // find linling_node before target son_node (so that can bypass target son_node ) :
    if(father->head == NULL){ 
        printf("Your target_node has no children_node ! \n\n") ;
        return ;
    }else if(father->head->next == NULL){  // only one child node :
        father->head->node->parent = NULL ;
        father->head = NULL ;
        father->tail = NULL ;
    }else{
            //bypass case :
            while ( temp->next->node->element != target_element_of_son )
            {
                temp = temp->next ;
            } 
            temp->next = temp->next->next ; // bypass target linking_node.
         }
    

    father->node_count -- ;
}

// attach a son_tree to target_father_tree :
// what this founction is different from founuction "increase_node" is parameter : "int data" and "tree_node* son"
void attach( tree_node* father , tree_node* son )
{
    linking_node* new_linking_node = (linking_node* )malloc( sizeof(linking_node) ) ;
    new_linking_node->next = NULL ;
    new_linking_node->node = son ; // initialize new_linking_node.
    son->parent = father ;

    if (father->tail == NULL || father->head == NULL){ // only judge tail or head either OK.
        father->head = new_linking_node ;
        father->tail = new_linking_node ;
    }else{
        father->tail->next = new_linking_node ;
        father->tail = father->tail->next ;// Operation complextion = O(1) ;
    }
    father->node_count ++ ;
}

int main()
{
    tree_node* root = (tree_node*)malloc( sizeof(tree_node) ); // layer 1 : root node.
    root->element = 0;
    root->parent = NULL;
    root->head = NULL;
    root->tail = NULL;
    root->node_count = 0;
    
    // insert node :
    tree_node* a1 = increase_node( root , 10 ) ;
    tree_node* a2 = increase_node( root , 20 ) ;
    tree_node* a3 = increase_node( root , 30 ) ; // layer 2 

    tree_node* a1b1 = increase_node( a1 , 40 ) ;
    tree_node* a1b2 = increase_node( a1 , 50 ) ;
    tree_node* a3b1 = increase_node( a3 , 60 ) ; // layer 3

    tree_node* a1b1c1 = increase_node( a1b2 , 70 ) ;
    tree_node* a3b1c1 = increase_node( a3b1 , 80 ) ; // layer 4

    printf("\n") , traverse(root) , printf("\n\n")  ;
    
    // detect element in node :x
    printf("a1 :     %d \n" , a1->element );       // 10
    printf("a1b2 :   %d \n" , a1b2->element );     // 50
    printf("a1b1c1 : %d \n" , a1b1c1->element );   // 70
    printf("a3b1c1 : %d \n\n" , a3b1c1->element ); // 80

    // simply test for easy_founctions :
    printf("Does a1b2 has a brother node? answer : %d \n" , has_brother(a1b2) );
    printf("children number of a1 node: %d\tchildren number of a3b1: %d\n\n" , children_nums(a1) , children_nums(a3b1) ) ;
    printf("  Is a3b1c1 leaf node ?  answer : %d \n  Is a3 leaf node ?  answer : %d\n\n" , is_leaf(a3b1c1) , is_leaf(a1) );


    detach(a3 , 60) ;
    printf("  After detach a3b1 from a3 , Is a3 leaf node ?  answer : %d\n\n" , is_leaf(a3) );
    detach(a1b2 , 70) ;
    printf("  After detach a1b1c1 from a1b1 , Is a1b1 leaf node ?  answer : %d\n\n" , is_leaf(a1b2) );
    //rubustness :
    printf("Attempting to cut after a1b1 , who has no child node : \n") ;
    detach(a1b1 , 100000) ;
    
    attach( a3 , a3b1 ) ;

    printf("Attach a3 tree to a2 node : \n") ;    
    attach( a2 , a3 ) ; // attach a1 tree to a2 node !
    printf("Having extended a2 tree !\nnow : a2--a3--a3b1--a3b1c1 ! " ) ;
    
    printf("\n") , traverse(root) , printf("\n\n")  ;

    free(root),free(a1),free(a2),free(a3),free(a1b1),free(a1b2),free(a3b1),free(a1b1c1),free(a3b1c1);
    return 0 ;
    // Demonstration over ......
}
/*
simple graphy below :

layer 1                      root
                           /  |  \
                          /   |   \
layer 2                 10   20    30    -------------a
                      /   \         \
layer 3             40     50        60    -----------b  , a3b1 soon be detached from a3. 
                           |          \
layer 4                    70          80     --------c

*/