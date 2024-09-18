/*
This shows the coding basics of circular-linked-list in C programming.
【实验题 1】在单链表和 &循环链表& 的现有demo程序基础上，
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
struct node *tail = NULL;   //new -> compared to the first vertion.
struct node *current = NULL;
// insert after target position ; 
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
      //if "position" is bigger than curcle list ,insert at (position % length).
      current = current->next ;
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

bool isEmpty() 
{
   return head == NULL;
}

int length() 
{
   int length = 0;

   //if list is empty
   if(head == NULL) 
   {
      return 0;
   }

   current = head->next;

   // here different to single linked list
   while(current != head) 
   {
      length++;
      current = current->next;   
   }
	
   return length;
}

//insert link at the first location
void insertFirst(int key, int data) 
{
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
   link->key = key;
   link->data = data;
	
   // attention here, difference
   if (isEmpty()) 
   {
      head = link;
      head->next = head;//curcle !
      tail = head;
   } 
   else 
   {
      //point it to old first node
      link->next = head;
		
      //point first to new first node
      head = link;

      //update tail node
      tail->next = head; //curcle !
   }  
   //printf("%p,%d,%d,%p\n",link,link->data,link->key,link->next);
   //printf("current head: %p\n",head);
   //printf("current tail->next: %p\n",tail->next);  
}

//delete first item
struct node *deleteFirst() 
{

   //save reference to first link
   struct node *tempLink = head;
	
   if(head->next == head) 
   {  
      head = NULL;
      return tempLink;
   }     

   //mark next to first link as first 
   head = head->next;

   //update tail node
   tail->next = head;
	
   //return the deleted link
   return tempLink;
}

//display the list
void printList() 
{

   struct node *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   if(head != NULL) 
   {
      // difference here
      while(ptr->next != head) 
      {
         //printf("(%d,%d) ",ptr->key,ptr->data);
         printf("(%p,%d,%d,%p) ",ptr,ptr->key,ptr->data,ptr->next);
         ptr = ptr->next;
      }

      //print the last node
      //printf("(%d,%d) ",ptr->key,ptr->data);
      printf("(%p,%d,%d,%p) ",ptr,ptr->key,ptr->data,ptr->next);
   }
	
   printf(" ]");
}

int main() 
{
   insertFirst(1,10);
   insertFirst(2,20);
   insertFirst(3,30);
   insertFirst(4,40);
   insertFirst(5,50);
   insertFirst(6,60); 
   printf("Original List: "); 
   printList();
   printf("\n\n");

   delete(5);
   printf("\nList after deleting an item: ");
   printList();
   printf("\n\n");
   
   insert(3 , 100 , 100); //insert after 3th node .
   printf("\nList after inserting an item: ");
   printList();
   printf("\n\n");   
 
   return 0;
}

