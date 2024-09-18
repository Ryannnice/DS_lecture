/*
Author: Qinbing Fu
Date: 2023 May
This introduces breadth-first and depth-first traversals of graph in C programming.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5
#define NOT_FOUND -1 

//function prototypes
//queue : to hold //*vertex index*//
void insert(int);
int removeData(void);
bool isQueueEmpty(void);
//stack
void push(int);
int pop(void);
int peek(void);
bool isStackEmpty(void);
//graph
void addVertex(char);
void addEdge(int,int);
void displayVertex(int);
int getAdjUnvisitedVertexIndex(int);
//traversal
void breadthFirstSearch(void);
void depthFirstSearch(void);


//Initialize :
//queue variables
int queue[MAX];
int rear = -1;
int front = 0;
int queueItemCount = 0;
//stack variables
int stack[MAX];
int top = -1;
//graph variables
//graph vertex struct
struct Vertex
{
   char label;
   bool visited;
};
//array of vertices
struct Vertex* lstVertices[MAX] ;
//adjacency matrix
int adjMatrix[MAX][MAX] ;
//vertex count
int vertexCount = 0 ; 


/**************************queue functions************************************/
//insert item
void insert(int data)
{
   queue[++rear] = data;
   queueItemCount++;
}
//remove item
int removeData()
{
   queueItemCount--;
   return queue[front++]; 
}
//check queue empty
bool isQueueEmpty()
{
   return queueItemCount == 0;
}

/**************************stack functions************************************/
//push item
void push(int item)
{ 
   stack[++top] = item;
} 
//pop item
int pop()
{ 
   return stack[top--];
}
//top of stack
int peek()
{
   return stack[top];
}
//check stack empty
bool isStackEmpty()
{
   return top == -1 ;
}

/**************************graph functions************************************/
//add vertex to the vertex list
void addVertex(char label)
{
   struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex)) ;
   vertex->label = label ;
   vertex->visited = false ;   //unvisited initialization
   lstVertices[vertexCount++] = vertex ;  // put "node" into its corrensponding array_list
}
//add edge, record in the //*adjacency matrix*//
void addEdge( int start , int end )
{
   adjMatrix[start][end] = 1 ;
   adjMatrix[end][start] = 1 ;
}

//display the vertex
void displayVertex(int vertexIndex) // (input INDEX at array_list)
{
   printf("%c ",lstVertices[vertexIndex]->label);
}

//get the adjacent && unvisited vertex
int getAdjUnvisitedVertexIndex(int vertexIndex)
{
   int i;

   for(i = 0; i<vertexCount; i++)
   {
      if(adjMatrix[vertexIndex][i] == 1 //check adjacency
         && lstVertices[i]->visited == false   //check if visited
      )
         return i;
   }
	
   return NOT_FOUND ;
}

//breadth-first traversal
void breadthFirstSearch()
{
   int i ;

   //mark first node as visited
   lstVertices[0]->visited = true ;
   //display the vertex
   displayVertex(0) ;

   // enqueue //*vertex index*// in queue
   insert(0) ;

   int unvisitedVertex ; 

   while( !isQueueEmpty() )
   {
      //get the unvisited vertex of vertex which is at front of the queue
      int dequeueVertexIndex = removeData() ; // hold dequeue element.

      //adjacent vertex found
      while( (unvisitedVertex = getAdjUnvisitedVertexIndex(dequeueVertexIndex) ) != NOT_FOUND )
      {    
         lstVertices[unvisitedVertex]->visited = true;
         displayVertex(unvisitedVertex);
         insert(unvisitedVertex);        
      }
   }

   //queue is empty, search is completed, reset the visited flag        
   for( i = 0 ; i<vertexCount ; i++ )
   {
      lstVertices[i]->visited = false ;
   }
}

//depth-first traversal
void depthFirstSearch()
{
   int i;

   //mark first node as visited
   lstVertices[0]->visited = true;

   //display the vertex
   displayVertex(0);

   //push vertex index in stack
   push(0);

   while( !isStackEmpty() ) 
   {
      //get the unvisited vertex of vertex which is at top of the stack
      int unvisitedVertex = getAdjUnvisitedVertexIndex(peek() ) ;

      //no adjacent vertex found
      if(unvisitedVertex == -1)
      {
         pop() ;
      }
      else
      {
         lstVertices[unvisitedVertex]->visited = true;
         displayVertex(unvisitedVertex);
         push(unvisitedVertex);
      }
   }

   //stack is empty, search is complete, reset the visited flag        
   for(i = 0;i < vertexCount;i++)
   {
      lstVertices[i]->visited = false;
   }
}

int main()
{
   int choice ;

   // set adjacency matrix to 0 :
   for( int i=0 ; i < MAX ; i++ ) 
   {
      for( int j=0 ; j < MAX ; j++ )       
         adjMatrix[i][j] = 0;
   }

   // put vertex into an "array" :
   addVertex('A');   // 0
   addVertex('B');   // 1
   addVertex('C');   // 2
   addVertex('D');   // 3
   addVertex('E');   // 4
 
   // add_Edge "1" element at //*both top and bottom*// traingle part of the matrix : 
   addEdge(0, 1);    // A - B
   addEdge(0, 2);    // A - C
   addEdge(0, 3);    // A - D
   addEdge(1, 4);    // B - E
   addEdge(2, 4);    // C - E
   addEdge(3, 4);    // D - E
	
   printf("Your choice( 1 breadth-first-search ; 2 depth-first-search ) : " ) ;
   scanf("%d", &choice) ;
   switch (choice)
   {
   case 1:
      printf("\nBreadth First Search:\n");
      breadthFirstSearch();
      break;
      
   case 2:
      printf("\nDepth First Search:\n");
      depthFirstSearch();
      break;
   
   default:
      break;
   }

   printf("\n");
   // check adjacency matrix
   for( int i = 0 ; i < MAX ; i++ )
   {
      for( int j = 0 ; j < MAX ; j++ )
      {
         printf("%d ", adjMatrix[i][j]);
      }
      printf("\n");
   }

   return 0;
}

