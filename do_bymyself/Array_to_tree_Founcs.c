/*
Author: Qinbing Fu , Renyvan Liu.
Date: 2023 Apr
This introduces an implementation of tree creation and traversal in C programming.
added : transform an array to a full binary tree.
1. in-order traversal
2. pre-order traversal
3. post-order traversal
4. transformation 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct node 
{
   //node data stored
   int data; 
	
   //children pointers
   struct node *leftChild;
   struct node *rightChild;
}node ;

struct node *root = NULL ;

void insert(int data)
{
   struct node *tempNode = (struct node*) malloc(sizeof(struct node));
   struct node *current;
   struct node *parent;

   tempNode->data = data;
   tempNode->leftChild = NULL;
   tempNode->rightChild = NULL;

   //if tree is empty
   if(root == NULL)
   {
      root = tempNode;
   } 
   else
   {
      current = root;
      parent = NULL;

      while(1)
      {
         parent = current;
         
         //go to left of the tree
         if(data < parent->data)
         {
            current = current->leftChild;
            
            //insert to the left
            if(current == NULL)
            {
               parent->leftChild = tempNode;
               return;
            }
         }  //go to right of the tree
         else
         {
            current = current->rightChild;

            //insert to the right
            if(current == NULL)
            {
               parent->rightChild = tempNode;
               return;
            }
         }
      }
   }
}

// put "i" into a tree_node :
node* to_node(int i )
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = i ;
    new_node->leftChild = NULL ;
    new_node->rightChild = NULL ; 
    return new_node ;
}

void attach(node** father, node* son)
{
    if (*father == NULL || son == NULL) {
        return ;
    }

    if ((*father)->leftChild == NULL) {
        (*father)->leftChild = son;
    } else if ((*father)->rightChild == NULL) {
        (*father)->rightChild = son;
    } else {
        return ;
    }
}

// return parents node.
node* FindParent(node* target_node, int num) {
    // case 1: root node has no parents.
    if (target_node && target_node->data == num ){
        return NULL ;
    }

    // case 2: searching leaf node case.
    //         In recurtion search , if searched to leaf_node but still not found correct node , 
    //         it will recurtion search leaf_node's left_son_node , which is NULL. Then this case appeared.
    if(target_node == NULL ){
        return NULL ;
    }

    // case 3: son_node's parents_node is root , just return root.
    if ( (target_node->leftChild != NULL && target_node->leftChild->data == num) || (target_node->rightChild != NULL && target_node->rightChild->data == num) ) {
        return target_node;
    }

    // case 4 : need to search from deeper !
    // recursion search from left : 
    node* temp = FindParent(target_node->leftChild, num);
    
    if (temp != NULL) { // found node
        return temp ;
    }
    // not found from left , search from right :
    return FindParent(target_node->rightChild, num);

}

// RECURTION version of founction "search" : input data , output corresponding node in the tree.
node* recursion_search(node* target_node , int num)
{
   // if NULL , no searching.
   if (target_node == NULL) {
      return NULL;
   }

   // start searching:

   // case1 : target_node is perfectly the node we wanted :
   if (target_node->data == num) {
      return target_node;
   } 

   // case2 : target_node has two son.  We need to search first at left_son ,then second at right_son. 
   else if (target_node->leftChild && target_node->rightChild) {  

      node* temp = recursion_search(target_node->leftChild, num);// search left_son at first.

      // Have founed "num" , just return temp whose payload is "num" :
      if (temp != NULL ) {
         return temp;
      } 
      // "temp" is NULL , which means we haven't find "num" from left_son : 
      else {
         return recursion_search(target_node->rightChild, num);// search right_son
      }
   }

   // case3 : target_node has only one son :
   else if (target_node->leftChild) {
      return recursion_search(target_node->leftChild, num);
   } else if (target_node->rightChild) {
      return recursion_search(target_node->rightChild, num);
   } 
   // case4 : target_node has no son : 
   else {
      return NULL;
   }

}

// Simplified Recurtion version.
node* recurtion_search2(node* target_node , int num) 
{
   if(target_node == NULL ){
      return NULL ;
   }else if(target_node->data == num ){
      return target_node ;
   }else{
      node* left_searcher = recurtion_search2(target_node->leftChild , num ) ; // Core 

      if(left_searcher){
         return left_searcher ;
      }else{
         return recurtion_search2(target_node->rightChild , num) ;
      }
      return NULL ;
   }

   return NULL ;
}

// Math method version of founction "search" : input index of array , output corresponding node in the tree.
// this algorithm is better than "recurtion_search".
// Using stack.
node* math_search(node* target_node , int index )
{
   int stack[10] ;
   memset(stack , 0 , sizeof(stack) ) ;
   int top = -1 ;

   //push : 
   for(int i = 0 ; index > 1 ; i++ , index /= 2 , top ++ )
   {
      stack[i] = index % 2 ;
   }
   //pop : 
   node* temp = target_node ;
   for(top ; top >= 0 ; top -- )
   {
      if(stack[top] == 1 ){
         temp = temp->rightChild ;
      }else// stack[top] == 0 :
         temp = temp->leftChild ;
   }
   return temp ;

}

struct node* search(int data)
{
   struct node *current = root;
   printf("Visiting elements: ");

   while(current->data != data)
   {
      if(current != NULL)
         printf("%d ",current->data);

      //go to left tree
      if(current->data > data)
      {
         current = current->leftChild;
      }
      //else go to right tree
      else
      {                
         current = current->rightChild;
      }

      //not found
      if(current == NULL)
      {
         return NULL;
      }
   }
   
   return current;
}

// insert a node with data as argument, at left leaf nodes
struct node* insectAtLeaf(node* target_node , int data)
{
   node* new_node = to_node(data) ;
   node* temp = target_node ;
   
   while(temp->leftChild )
   {
      temp = temp->leftChild ;
   }
   temp->leftChild = new_node ;

   return new_node ;
}

// delete a node with data as argument
node* deleteNode(node* target_node , int num )
{
   node* deleteNode = NULL ;
   node* parents = FindParent(target_node , num ) ;
   if(parents){
      if(parents->leftChild->data = num ){
         deleteNode = parents->leftChild ;
         parents->leftChild = NULL ;
         return deleteNode ;
      }else{
         deleteNode = parents->rightChild ;
         parents->rightChild = NULL ;
         return deleteNode ;
      }
   }

   return NULL ;
}

// find the size of a tree
int size(node* root) 
{
   if (root == NULL) {
       return 0;
   } else if (root->leftChild == NULL && root->rightChild == NULL) {
       return 1;
   } else {
       int leftSize = size(root->leftChild);
       int rightSize = size(root->rightChild);

       return leftSize + rightSize + 1;
   }

}

// return the size of a tree
int height(node* root) 
{
   if (root == NULL) {
       return 0;
   } else {
       int left = height(root->leftChild);
       int right = height(root->rightChild);

       return (left > right ? left : right) + 1;
   }

}

void pre_order_traversal(struct node* root)
{
   if(root != NULL)
   {
      printf("%d ",root->data);
      pre_order_traversal(root->leftChild);
      pre_order_traversal(root->rightChild);
   }
}

void inorder_traversal(struct node* root)
{
   if(root != NULL)
   {
      inorder_traversal(root->leftChild);
      printf("%d ",root->data);
      inorder_traversal(root->rightChild);
   }
}

void post_order_traversal(struct node* root)
{
   if(root != NULL)
   {
      post_order_traversal(root->leftChild);
      post_order_traversal(root->rightChild);
      printf("%d ", root->data);
   }
}


// **Array tramsform to Tree** : 

int parents_index(int i )
{
    return i/2 ;
}

void Array_to_Full_Binary_Tree(int* arr , int arr_num , node** tree_root ) // core founction.
{
    for(int i = 1 ; i < arr_num ; i ++ ) 
    {
        node* son_node = to_node(arr[i]);

        if(i == 1 ) {
            *tree_root = son_node ;
        } else {
            
            node* temp = math_search(*tree_root , parents_index(i) ); // "math_search" algorithm is better than "recurtion_search".
            //node* temp = recursion_search(*tree_root , arr[parents_index(i)] );

            attach(&temp , son_node);
        }
    }
}


int main()
{
   int i;
   int array[SIZE] = { 10, 11, 20, 22, 30, 33, 40, 44, 50, 55 };

   for(i = 0; i < SIZE; i++)
      insert(array[i]);

   printf("%d root\n", root->data);

   i = 11;
   struct node * temp = search(i);

   if(temp != NULL)
   {
      printf("[%d] Element found....", temp->data);
      printf("\n");
   }
   else
   {
      printf("[ x ] Element not found (%d)....\n", i);
   }
 
   i = 66;
   temp = search(i);

   if(temp != NULL)
   {
      printf("[%d] Element found....", temp->data);
      printf("\n");
   }
   else
   {
      printf("[ x ] Element not found (%d)....\n", i);
   }

   printf("\nPreorder traversal: ");
   pre_order_traversal(root);

   printf("\nInorder traversal: ");
   inorder_traversal(root);

   printf("\nPost order traversal: ");
   post_order_traversal(root);
   


                  /* Transform an Array to a Full_Tree  Operation */

   int array2[13] = {  0 , 3 , 9 , 5 , 14 , 10 , 6 , 8 , 17 , 15 , 13 , 23 , 12 } ;
/* element_index  :  | 0 | 1 | 2 | 3 | 4  | 5  | 6 | 7 | 8  | 9  | 10 | 11 | 12 |

   tips :   
      # The first element is meaningless , accroding to teaching PPT .
      # In this array , ( an element's parents' index )  =  ( this element's index )/2 .
        take "23" as an example : its index is 11 , so its parents' index is 11/2 = 5 , which means "10" is parents of "23" . 
      # simple graphy :
                                          3
                                      /       \
                                    9           5
                                 /    \        /   \
                              14       10     6     8
                            /   \     /  \    |
                          17    15   13  23   12
*/
 
   node *Array_Transformed_Tree = (node* )malloc(sizeof(node* ) );// this tree is transformed from "array2".
   printf("\n\n\n**Transform an Array to a Full_Tree  Operation**\n" ) ;

   // operation
   Array_to_Full_Binary_Tree( array2 , 13 , &Array_Transformed_Tree ) ;

   // traversal
   printf("\nTransformed Tree :") ;
   printf("\nPreorder traversal:");
   pre_order_traversal(Array_Transformed_Tree ) ;
   printf("\nInorder traversal: ");
   inorder_traversal(Array_Transformed_Tree ) ; 
   printf("\nPost order traversal: ");
   post_order_traversal(Array_Transformed_Tree ) ;


   // Founction "recursion_search" :
   printf("\n\nFounction 'recursion_search'  :\n") ;
   node* temp1 = recursion_search(Array_Transformed_Tree , 12 );
   printf("node in Array_Transformed_Tree whose element is 12: %d\n\n" , temp1->data ) ;
 
   // Founction "math_search" :
   printf("Founction 'math_search'  :\n") ;
   node* temp2 = math_search(Array_Transformed_Tree , 10) ;
   printf("node in Array_Transformed_Tree whose index is 10: %d\n\n" , temp2->data) ;

   // Founction "FindParent" :
   printf("Founction 'FindPraents'  :\n") ;
   node* parents = FindParent(Array_Transformed_Tree , 12 ) ;
   printf("'12' node's parents is node : '%d' \n\n" , parents->data ) ;

   // Founction "insectAtLeaf" :
   printf("Founction 'insectAtLeaf'  :\n") ;
   node* leaf = insectAtLeaf(Array_Transformed_Tree , 10086 ) ;
   printf("pre_order_traverse tree after adding this node : \n" ) ;
   pre_order_traversal(Array_Transformed_Tree ) ;   

   // Founction "delete" :
   printf("\n\nFounction 'delete'  :\n") ;
   node* deleted_Node = deleteNode(Array_Transformed_Tree , 10086 ) ;
   printf("node been deleted is : %d\n" , deleted_Node->data ) ;
   printf("pre_order_traverse tree after delete this node : \n" ) ;
   pre_order_traversal(Array_Transformed_Tree ) ;

   // Founction "size" :
   printf("\n\nFounction 'size'  :\n") ;
   printf("Size of this tree is : %d " , size(Array_Transformed_Tree) ) ;

   // Founction "height" :
   printf("\n\nFounction 'height'  :\n" ) ;
   printf("Height of this tree is : %d " , height(Array_Transformed_Tree ) ) ;


   // Founction "recurtion_search2" :
   printf("\n\nFounction 'recurtion_search2'  :\n") ;
   node* temp3 = recurtion_search2(Array_Transformed_Tree , 13 ) ;
   printf("Element : %d founded \n\n" , temp3->data ) ;


   // Demostration over ...
   return 0;
}

