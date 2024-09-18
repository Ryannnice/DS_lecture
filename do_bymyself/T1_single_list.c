/*
This shows the coding basics of single-linked-list in C programming.
【实验题 1】在 &单链表& 和循环链表的现有demo程序基础上，
编写从链表中间位置删除和插入元素的算法。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
   int data;
   int key;
   struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

// insert node after target node : enter potision , insert after "position".
struct node* insert(int position , int key , int data )
{
   //robustness :
   if(position < 1 )
   {
      printf("WRONG inserting position ! \n") ;
      return NULL ;
   }
   current = head ;
   struct node* new_node = (struct node*)malloc(sizeof(struct node)) ;
   new_node->key = key ;
   new_node->data = data ;
   new_node->next = NULL ;//initialize over !

   //find target position :
   for(int i = 1 ; i < position ; i++ )
   {
      if(current->next != NULL)
         current = current->next ;
      else  // robustness :
      {
         printf("WRONG inserting position ! \n");
         return NULL ;
      }
   }
   //insert operation :
   new_node->next = current->next ;
   current->next = new_node ;

}
//delete a link with given key
struct node* delete(int key) 
{

   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;
	
   //if list is empty
   if(head == NULL) 
   {
      return NULL;
   }

   // traverse list :
   while(current->key != key) 
   {
      //if it is last node
      if(current->next == NULL) 
      {
         return NULL;
      } 
      else 
      {         // go on :
         previous = current;
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head)  //case that need to delete the first node : just bypass the "head".
   {
      head = head->next;
   }
   else  // bypass the current link.
   {  
      previous->next = current->next;
   }    
	
   return current;
}

//display the list.
void printList() 
{
   // reset to head
   struct node *ptr = head;
   //printf("\nhead address: %p\n", head);
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) 
   {
      printf("(%d,%d,%p) ",ptr->key,ptr->data,ptr->next);
      //printf("(%d,%d) ",ptr->key,ptr->data);
      ptr = ptr->next;
   }
	//end at the last node

   printf(" ]");
}

//insert link at the first location
void insertFirst(int key, int data)
{
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->key = key;
   link->data = data;
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
   //printf("current head address: \n%p\n", head);
}

//is list empty
bool isEmpty() 
{
   return head == NULL;
}

//find a link with given key
struct node* find(int key) 
{

   //start from the first link
   struct node* current = head;

   //if list is empty
   if(head == NULL) 
   {
      return NULL;
   }

   //navigate through list
   while(current->key != key) 
   {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}

void main() 
{
   // insert node from the beginning
   insertFirst(1,10);
   insertFirst(2,20);
   insertFirst(3,30);
   insertFirst(4,40);
   insertFirst(5,50);
   insertFirst(6,60); 
   insertFirst(7,70);
   
   printf("Original List: "); 
   printList();
   printf("\n");  
   printf("\n");  

   delete(6);
   printf("List after deleting an item: ");
   printList();
   printf("\n");
   printf("\n");

   insert(5 , 10086 , 10087) ;
   printf("List after adding an item : ");
   printList();
   printf("\n");
   printf("\n");
   
   printf("Robustness testing: When insert at wrong position : \n");
   insert(10 , 100 , 100) ;
   insert(-1 , 100 , 100) ;

   insert(3 , 123 , 10087) ;
   printf("\nList after adding an another item : ");
   printList();

   printf("\n\ndeleting and adding operation successfully achieved !!! \n");
}

