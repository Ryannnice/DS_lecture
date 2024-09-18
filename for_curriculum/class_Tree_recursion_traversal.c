/*
Author: Qinbing Fu
Date: 2023 Apr
This introduces an implementation of tree creation and traversal in C programming.
1. in-order traversal
2. pre-order traversal
3. post-order traversal
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node 
{
   //node data stored
   int data; 
	
   //children pointers
   struct node *leftChild;
   struct node *rightChild;
}node ;

struct node *root = NULL;

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

// insert a node with data as argument, at any leaf nodes
struct node* insectAtLeaf(int data)
{}

// RECURTION version of founction "search" !
struct node* recursion_search(node* target_node , int num) // attempt to find num from node's son_node.
{
   if(target_node == NULL ){
      return NULL ;
   }

   struct node* temp = target_node ;

   if (temp->data == num ){
      return temp ; // Final return at here.
   }else if(temp->leftChild || temp->rightChild){

      if(temp->leftChild){
         recursion_search(temp->leftChild , num ) ;
      }else{
         recursion_search(temp->rightChild , num ) ;
      }
   }

}

// return target_node's parents , and their relationship such as "leftChild"
struct node* FindParent(node* target_node , int num) // attempt to find num from node's son_node.
{
   if(target_node == NULL ){
      return NULL ;
   }

   struct node* parent = target_node ; // this node is used for saving position of parent , which is convenient to RETURN.

   if(parent->leftChild->data == num || parent->rightChild->data == num){
      return parent ;
   }else if(parent->leftChild || parent->rightChild){

      if(parent->leftChild){
         recursion_search(parent->leftChild , num ) ;
      }else{
         recursion_search(parent->rightChild , num ) ;
      }
   }

}

// delete a node with data as argument
struct node* deleteNode(int num)
{
   node* parent = FindParent(root , num) ; // have found the parent node that need to be operated, and allocate it to node named "parent"
   node* deleted_node = (node* )malloc(sizeof(node*) ) ; // to store position of deleted_son_node.

   if(parent->leftChild){
      if(parent->leftChild->data == num){
         deleted_node = parent->leftChild ;
         parent->leftChild = NULL ;
      }
   }else{
      deleted_node = parent->rightChild ;
      parent->rightChild = NULL ;
   } 

   return deleted_node ;
}

// find the size of a tree
int size()
{}

// return the size of a tree
int height()
{}

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


   
/*
   // Founction "find" :
   node* finded = recursion_search(root , 40 );
   printf("\n\ndata : \n%d\nposition : \n%d\n\n " , finded->data , &finded ) ;
   
   // Founction "delete" :
   node* deleted_Node = (node*)malloc(sizeof(node* ) ) ;

   deleted_Node = deleteNode(33) ;

   pre_order_traversal(root ) ;
*/

   return 0;
}

