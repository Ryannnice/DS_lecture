/*
This shows the coding basics of double-linked-list in C programming.
Note the double linked list here is not circular.
【实验题 2】将现有双向链表的demo程序改写为循环双向链表。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node 
{
   int data;
   int key;

	struct node *prev;
   struct node *next;
};

//this link always point to first Link
struct node *head = NULL;

//this link always point to last Link 
struct node *last = NULL;
struct node *current = NULL;

//is list empty
bool isEmpty() 
{
   return head == NULL;
}

int length() 
{
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next)
   {
      length++;
   }
	
   return length;
}

//display the list in from first to last
void displayForward() 
{

   //start from the beginning
   struct node *ptr = head;
	
   //navigate till the end of the list
   printf("\n[ ");
	
   while(ptr != last) 
   {     
      //print data   
      printf("(%p,%d,%d,%p) ",ptr->prev , ptr->key,ptr->data , ptr->next);
      //printf("(%p,%p,%d,%d,%p) ",ptr->prev,ptr,ptr->key,ptr->data,ptr->next);
      
      //traverse forward to next node
      ptr = ptr->next;
   }
      printf("(%p,%d,%d,%p) ",last->prev , last->key,last->data , last->next);
	
   printf(" ]\n");
}

//display the list from last to first
void displayBackward() 
{

   //start from the last
   struct node *ptr = last;
	
   //navigate till the start of the list
   printf("\n[ ");
	
   while(ptr != head) 
   {
      //print data
      printf("(%p,%d,%d,%p) ",ptr->prev,ptr->key,ptr->data,ptr->next);
      //printf("(%p,%p,%d,%d,%p) ",ptr->prev,ptr,ptr->key,ptr->data,ptr->next);
		
      //traverse backward to next node
      ptr = ptr ->prev;
   }
   
   //print the first node
   printf("(%p,%d,%d,%p) ",head->prev,head->key,head->data,head->next);
   //printf("(%p,%p,%d,%d,%p) ",ptr->prev,ptr,ptr->key,ptr->data,ptr->next);

   printf(" ]\n");
}

//insert link at the first location
void insertFirst(int key, int data) 
{

   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
   link->key = key;
   link->data = data;
	
   if(isEmpty()) 
   {
      link->next = link ;
      link->prev = link ;
      head = link;
      last = link;
   } 
   else 
   {
      link->next = head;
      last->next = link;
      head->prev = link;
      link->prev = last;
      head = link ;
   }

}

//insert link at the last location
void insertLast(int key, int data) 
{

   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
   link->key = key;
   link->data = data;
	
   if(isEmpty()) 
   {
      link->next = link;
      link->prev = link;
      head = link;
      last = link;
   } 
   else 
   {
      link->next = head;
      last->next = link;
      link->prev = last;
      head->prev = link;
      last = link ;     
   }
}

//delete first item
struct node* deleteFirst() 
{
   if(head == NULL)
   return NULL ;
   //save reference to first link
   struct node *tempLink = head;
	
   //if only one link
   if(head == last)
   {
      last = NULL,head = NULL ; //delete the only node .
   } 
   else 
   {
      last->next = head->next;

      head->next->prev = head->prev; //which means drop "head" node.
   }
	
   head = head->next;

   //return the deleted link
   return tempLink;
}

//delete link at the last location

struct node* deleteLast() 
{
   if(head == NULL)
   return NULL ;
   //save reference to first link
   struct node *tempLink = last;
	
   //if only one link
   if(head == last)
   {
      last = NULL,head = NULL ; //delete the only node .
   } 
   else 
   {
      head->prev = last->prev;
      
      last->prev->next = last->next; //which means drop "head" node.
   }
	
   last = last->prev;

   //return the deleted link
   return tempLink;
}

//delete a link with given key

struct node* delete(int key)
{
   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) 
   {
      //if it is last node	
      if(current->next == NULL) 
      {
         return NULL;
      } 
      else 
      {
         //store reference to current link
         previous = current;
			
         //move to next link
         current = current->next;             
      }
   }

   //found a match, update the link
   if(current == head) 
   {
      //change first to point to next link
      head = head->next;
   } 
   else 
   {
      //bypass the current link
      current->prev->next = current->next;
   }   
   if(current == last) 
   {
      //change last to point to prev link
      last = current->prev;
   } 
   else 
   {
      current->next->prev = current->prev;
   }
	
   return current;
}

bool insertAfter(int key, int newKey, int data) 
{
   //start from the first link
   struct node *current = head; 
	
   //if list is empty
   if(head == NULL) 
   {
      return false;
   }

   //navigate through list
   while(current->key != key) 
   {
      //if it is last node
      if(current->next == NULL) 
      {
         return false;
      } 
      else 
      {           
         //move to next node
         current = current->next;
      }
   }
	
   //create a link
   struct node *newLink = (struct node*) malloc(sizeof(struct node));
   newLink->key = newKey;
   newLink->data = data;

   //insert at the last position
   if(current == last) 
   {
      newLink->next = NULL; 
      last = newLink; 
   }
   //insert inside the list 
   else 
   {
      newLink->next = current->next;     
      current->next->prev = newLink;
   }
   newLink->prev = current; 
   current->next = newLink; 

   //success
   return true; 
}

void main() 
{
   //create list from the beginning
   insertFirst(1,10);
   insertFirst(2,20);
   insertFirst(3,30);
   insertFirst(4,40);
   insertFirst(5,50);
   insertFirst(6,60); 

   printf("\nTraversing the Double Linked List (First to Last): ");  
   displayForward();
	
   printf("\n");
   printf("\nTraversing the Double Linked List (Last to first): "); 
   displayBackward();

   printf("\nList---after deleting first node: ");
   
   struct node *temp = deleteFirst();
   printf("\nDeleted node:");  
   printf("(%d,%d) ",temp->key,temp->data);
   displayForward();

   printf("\nList---after deleting last node: ");  
   deleteLast();
   displayForward();

   //insertion
   printf("\nList---insert after key(4): ");  
   insertAfter(4,9,90);
   displayForward();

   printf("\nList---after delete key(5): ");  
   delete(5);
   displayForward();
   
   printf("\nDouble linked lisk operation completed......");
}

