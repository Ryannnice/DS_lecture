/*
作者：刘稔远  信安221
该C程序展示用 链表 构建 栈，解决 逆波兰表达式解析 问题
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXSIZE 30

/*  用链表构建栈（链表头作为栈顶） */

// 运算数栈 ：存放数字
typedef struct int_list_node
{
    int num ;
    struct int_list_node* next ;
    
}int_node ;

// 全局变量指向操作数栈 的栈顶 （即链表头）：
int_node* num_stack = NULL ;


/*  栈操作 函数  */

//入栈数字
void push_int(int item )
{
   //stack_int[++top_int] = item;
    int_node* new = (int_node* )malloc(sizeof(int_node ) ) ;
    
    new->num = item ;//赋值

    new->next = num_stack ; 
    num_stack = new ;//在头节点进行“入栈”（即插入链表头）操作
}

//出栈数字
int pop_int()
{
    int temp = num_stack->num ;
    num_stack = num_stack->next ;

    return temp ;
}


//计算后缀表达式
void evaluate( char *postfix_formula )
{
   char character ;
   int i = 0 ;
   int operand1 , operand2 ;

   while((character = postfix_formula[i++] ) != '\0' )
   {
      if(isdigit(character ) ){
	     push_int(character-'0' ) ;//若是数字： 操作数栈 入栈
      }else{
         //发现操作符，需要运算：先出栈 操作数栈栈顶的两个数，
         operand2 = pop_int() ;
         operand1 = pop_int() ;
			//运算结果 入栈 
         switch( character ) 
         {
            case '+':
               push_int(operand1+operand2 ) ;
               break ;
            case '-':
               push_int(operand1-operand2 ) ;
               break ;
            case '*':
               push_int(operand1*operand2 ) ;
               break ;
            case '/':
               push_int(operand1/operand2 ) ;
               break ;
         }
      }
   }
	
}

void main()
{
   char postfix_formula[MAXSIZE] = "12-3+4+567**-89*+" ;
   printf("Postfix_formula expression : %s\n" , postfix_formula ) ;
   evaluate(postfix_formula ) ; 
   printf("Answer is : %d\n" , num_stack->num ) ;
}

