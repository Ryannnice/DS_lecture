#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//struct  a  Node.
struct ListNode {  
      int val;
      struct ListNode *next;
 };
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *head = NULL, *tail = NULL ;
    int num1 , num2 ;
    int carry = 0; //number of carry.
    while (l1 || l2)   //l1 or l2 exists:
    {
        num1 =( l1 ? l1->val : 0 ); //allocate val of l1 to num1 , val of l2 to n2.
        num2 =( l2 ? l2->val : 0 );
        int sum = num1 + num2 + carry; //the value of a new list.

//////////////////////////////////////////////////////////////////////////////////////////
        if (!head) {     //head of the new list.                                        //
            head = tail = malloc(sizeof(struct ListNode));                              //
            tail->val = sum % 10;                                                       //
            tail->next = NULL;                                                          //
        } else {                                                                        //
            tail->next = malloc(sizeof(struct ListNode)); //enlarge the newlist.        //
            tail->next->val = sum % 10;   //allocate value.                             //
                                                                                        //
            tail = tail->next;     //the "new tail".                                    //
            tail->next = NULL;                                                          //
        }    //eventually , the size of newlist "+ 1".                                  //
//////////////////////////////////////////////////////////////////////////////////////////

        carry = sum / 10; //carry.
        if (l1) {
            l1 = l1->next; //move on.
        }
        if (l2) {
            l2 = l2->next; //move on.
        }
    }
    //add carry to tail.
    if (carry > 0) {
        tail->next = malloc(sizeof(struct ListNode));
        tail->next->val = carry;
        tail->next->next = NULL;
    }
    return head;
}

/*
 Definition for singly-linked list.
 struct ListNode {
     int val;
     struct ListNode *next;
 };
 struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode* head = NULL ; 
    struct ListNode* tail = NULL ;
    int num1 = 0 ,  num2 = 0 ,  carry = 0 ;
    int sub ;
    while( l1 || l2){
        num1 = (l1 ? l1->val : 0);
        num2 = (l2 ? l2->val : 0);
        sub = num1 + num2 + carry ;

        if(!head){
            head = tail = malloc (sizeof(struct ListNode));
            tail->val = sub % 10 ;
            tail->next = NULL ;
        }
        else {
            tail->next = malloc(sizeof(struct ListNode));
            tail->next->val = sub % 10 ;
            tail = tail->next ;
            tail->next = NULL ;

        }
        carry = sub / 10 ;
        if(l1)
        {l1 = l1->next;}
        if(l2)
        {l2 = l2->next;}
    } 
    if(carry > 0)
    {
        tail->next = malloc(sizeof(struct ListNode));
        tail->next->val = carry ;
        tail->next->next = NULL ;
    }
    return head ;
}
*/