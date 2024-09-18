/*
Author: Qinbing Fu
Date: 2023 Mar
This introduces expression parsing using stack.
*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXSIZE 25

//first stack
//create char stack
char stack_char[MAXSIZE];
int top = -1;

//second stack
//create int stack
int stack_int[MAXSIZE];
int top_int = -1;

void push_char(char item)
{
   stack_char[++top] = item;
}

char pop_char()
{
   return stack_char[top--];
}

void push_int(int item)
{
   stack_int[++top_int] = item;
}

char pop_int()
{
   return stack_int[top_int--];
}

//This function returns precedence of operators: 1->highest, 4->lowest.
int precedence(char symbol)
{

   switch(symbol)
   {
      case '+': 
      case '-':
         return 2; 
         break; 
      case '*': 
      case '/':
         return 3; 
         break; 
      case '^': 
         return 4; 
         break; 
      case '(': 
      case ')': 
      case '#':
         return 1; 
         break; 
   }
}

//This function checks whether the symbol is operator?
int isOperator(char symbol)
{
   switch(symbol) 
   {
      case '+': 
      case '-': 
      case '*': 
      case '/': 
      case '^': 
      case '(': 
      case ')':
         return 1;
      break; 
         default:
         return 0;
   }
}

//This function converts infix expression to postfix.
void convert(char infix[],char postfix[])
{
   int i,symbol,j = 0;
   stack_char[++top] = '#';
	
   for(i = 0;i<strlen(infix);i++)
   {
      symbol = infix[i];
		
      if(isOperator(symbol) == 0)
      {
         postfix[j] = symbol;
         j++;
      } 
      else 
      {
         if(symbol == '(') 
         {
            push_char(symbol); 
         } 
         else 
         {
            if(symbol == ')') 
            {
				
               while(stack_char[top] != '(') {
                  postfix[j] = pop_char(); 
                  j++; 
               } 
					
               pop_char();   //pop out (.
            } 
            else 
            {
               if(precedence(symbol)>precedence(stack_char[top])) 
               {
                  push_char(symbol); 
               } 
               else 
               {
                  while(precedence(symbol)<=precedence(stack_char[top])) 
                  {
                     postfix[j] = pop_char(); 
                     j++; 
                  } 
						
                  push_char(symbol); 
               }
            }
         }
      }
   }
   while(stack_char[top] != '#') 
   {
      postfix[j] = pop_char();
      j++;
   } 
	
   postfix[j]='\0';  //null terminate string.
} 

//This function evaluates postfix expression.
int evaluate(char *postfix)
{
   char ch;
   int i = 0,operand1,operand2;

   while( (ch = postfix[i++]) != '\0')
   {
      if(isdigit(ch))
      {
	     push_int(ch-'0');  // Push the operand
      } 
      else
      {
         //Operator,pop two operands
         operand2 = pop_int();
         operand1 = pop_int();
			
         switch(ch) 
         {
            case '+':
               push_int(operand1+operand2);
               break;
            case '-':
               push_int(operand1-operand2);
               break;
            case '*':
               push_int(operand1*operand2);
               break;
            case '/':
               push_int(operand1/operand2);
               break;
         }
      }
   }
	
   return stack_int[top_int];
}

void main()
{
   char infix[MAXSIZE] = "1*(2+3)",postfix[MAXSIZE];
   convert(infix,postfix);
	
   printf("Infix expression is: %s\n" , infix);
   printf("Postfix expression is: %s\n" , postfix);
   printf("Evaluated expression is: %d\n" , evaluate(postfix));
}

