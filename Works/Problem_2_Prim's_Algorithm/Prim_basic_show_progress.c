/*
作者：刘稔远  信安221
该C程序展示用 [Prim算法] 解决 [最小生成树] 问题
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define VERTEX_NUM 12
#define NOT_FOUND -1 

////////////////////////////初始化////////////////////////////////////////////////////////

// 图
typedef struct Vertex
{
   char label ;
   bool visited ;

   int father ;// 存放父节点在VertexArray的索引值（构造父树时用）
   int distanceToTree ;// 装载 [顶点与树的距离]（定义正无穷值为：-1）
}V ;

// 顶点计数器
int vertexCount = 0 ; 

// [数组] 装载 [顶点]
V* VertexArray[VERTEX_NUM] ;

// [数组] 表示顶点是否在生成树里（0不在 / 1在）
int InTree[12] ;

// [邻接矩阵] 装载 [顶点间边长度]
int adjMatrix[VERTEX_NUM][VERTEX_NUM] ;//表示图
int TreeMatrix[VERTEX_NUM][VERTEX_NUM] ;//表示生成树


////////////////////////////函数声明////////////////////////////////////////////////////////

// 图
void addVertex(char);
void addEdge(int,int,int);
void addBranch(int,int,int);
void print(int);
void breadthFirstSearch(int);
void depthFirstSearch(int);
int getAdjUnvisitedVertexIndex(int);// core
bool isInTree(int);
// 邻接矩阵
void printMatrix(int);
void initializeMatrix();
void initializeTreeMatrix();
void PrimAlgorithm(int);


////////////////////////////函数////////////////////////////////////////////////////////


/* 图函数 */

// 1 : 添加 [顶点] 到 [顶点‘数组’]
// 2 : 初始化 [顶点到最小生成树的距离] 为 -1（即正无穷）
void addVertex(char label)
{
   V* vertex = (V* )malloc(sizeof(V ) ) ;

   vertex->label = label ;
   vertex->visited = false ;
   vertex->father = -1 ;
   vertex->distanceToTree = -1 ;// 初始化

   VertexArray[vertexCount++] = vertex ;// 顶点 放入[数组]
}

//找[相邻]并且[未被访问]的顶点
int getAdjUnvisitedVertexIndex( int vertexIndex )
{
   int i ;
   for( i = 0 ; i < vertexCount ; i ++ )
   {
      if(adjMatrix[vertexIndex][i] != -1 && VertexArray[i]->visited == false )
         {
            printf("\nAdjacency:%d " , i ) ;
            return i;
         }
   }
	printf("\nNo Adjacent Vertex Left \n") ;
   return NOT_FOUND ;
}
bool isInTree( int vertexIndex )
{
    return InTree[vertexIndex] ;
}
/* 邻接矩阵操作函数 */

//打印邻接矩阵  0:adjMatrix  1:TreeMatrix
void printMatrix(int choice)
{
   if( choice != 1 && choice != 0 ){
      printf("Error Choice ! \n" ) ;
      return ;
   }
   printf("   A    B    C    D    E    F    G    H    I    J    K    L\n") ;
   for( int i = 0 ; i < VERTEX_NUM ; i++ )
   {
      switch ( i )
      {
      case 0 :
         printf("A ") ;
         break;
      case 1 :
         printf("\nB ") ;
         break;
      case 2 :
         printf("\nC ") ;
         break;
      case 3 :
         printf("\nD ") ;
         break;
      case 4 :
         printf("\nE ") ;
         break;
      case 5 :
         printf("\nF ") ;
         break;
      case 6 :
         printf("\nG ") ;
         break;
      case 7 :
         printf("\nH ") ;
         break;
      case 8 :
         printf("\nI ") ;
         break;
      case 9 :
         printf("\nJ ") ;
         break;
      case 10 :
         printf("\nK ") ;
         break;
      case 11 :
         printf("\nL ") ;
         break;
      default:
         break;
      }

      if( choice == 0 ){
         for( int j = 0 ; j < VERTEX_NUM ; j++ )
         {
            if(adjMatrix[i][j] == -1 ){
               printf("[ ]  " ) ;
            }else if(adjMatrix[i][j] >= 10){
               printf("[%d] ", adjMatrix[i][j] ) ;
            }else{
               printf("[%d]  ", adjMatrix[i][j] ) ;
            }
         }
      }else{// choice == 1 
         for( int j = 0 ; j < VERTEX_NUM ; j++ )
         {
            if(TreeMatrix[i][j] == -1 ){
               printf("[ ]  " ) ;
            }else if(TreeMatrix[i][j] >= 10){
               printf("[%d] ", TreeMatrix[i][j] ) ;
            }else{
               printf("[%d]  ", TreeMatrix[i][j] ) ;
            }
         }
      }

      printf("\n") ;
   }
}

//初始化邻接矩阵各项(各边长度)为-1（即无穷大）
void initializeMatrix()
{
   for( int i=0 ; i < VERTEX_NUM ; i++ ) 
   {
      for( int j=0 ; j < VERTEX_NUM ; j++ )       
         adjMatrix[i][j] = -1 ;
   }
}
void initializeTreeMatrix()
{
   for( int i=0 ; i < VERTEX_NUM ; i++ ) 
   {
      for( int j=0 ; j < VERTEX_NUM ; j++ )       
         TreeMatrix[i][j] = -1 ;
   }
}

//在图的邻接矩阵中 添加边
void addEdge( int start , int end , int len )
{
   adjMatrix[start][end] = len ;
   adjMatrix[end][start] = len ;
}

//在生成树的邻接矩阵 添加树枝
void addBranch( int start , int end , int len )
{
   TreeMatrix[start][end] = len ;
   TreeMatrix[end][start] = len ;
}


void PrimAlgorithm( int startVertexIndex )
{
    //将根节点（到最小生成树）距离设置为 0 ,状态为：在树中
    VertexArray[startVertexIndex]->distanceToTree = 0 ; 
    InTree[startVertexIndex] = 1 ;

    int IndexOfMin = startVertexIndex ;
    
    for( int i = 0 ; i < vertexCount-1 ; i ++ )//迭代 vertexCount - 1 次
    {
        //找[相邻][未访问][不在树中]的顶点：
        int unvisitedVertex ;
        while ( ( unvisitedVertex = getAdjUnvisitedVertexIndex(IndexOfMin ) ) != NOT_FOUND )
        {
            // 将相邻顶点标记为已访问：
            VertexArray[unvisitedVertex]->visited = true ; 

            if( ( VertexArray[unvisitedVertex]->distanceToTree > adjMatrix[unvisitedVertex][IndexOfMin] )// 发现更小距离
                  || VertexArray[unvisitedVertex]->distanceToTree < 0 )// 或者：距离无限大
            {
                VertexArray[unvisitedVertex]->distanceToTree = adjMatrix[unvisitedVertex][IndexOfMin] ;
                VertexArray[unvisitedVertex]->father = IndexOfMin ;
               printf("\ndistance:%d Father :%d" , VertexArray[unvisitedVertex]->distanceToTree , VertexArray[unvisitedVertex]->father ) ;
            }
        }

        for( int i = 0 ; i < vertexCount ; i ++ )
        {
            VertexArray[i]->visited = false ;
        }

        //经过上一步更新记录后，寻找距离生成树距离最小的未访问节点，作为下一步的添加对象
        int MinDistance = 10000 , Index ;
        for( Index = 0 ; Index < vertexCount ; Index ++ )
        {
            if(   ( !isInTree(Index) )// 不在树中------------------------------------1
               && ( VertexArray[Index]->distanceToTree > 0 )// 与树相邻--------------2
               && ( VertexArray[Index]->distanceToTree < MinDistance ) )// 距离小----3
            {
                printf("\nMin_option has Changed to : %d " , Index ) ;
                MinDistance = VertexArray[Index]->distanceToTree ;
                IndexOfMin = Index ;//更新距离树最近的节点
            }
        }//现在，IndexOfMin就是下一步应该添加到树的节点的下标

        MinDistance = 10000 ;

        //把距离树最近的节点添加到树的邻接矩阵TreeMatrix , 两个顶点为[距离树最近的顶点]和它的的[父节点]
        addBranch( IndexOfMin , VertexArray[IndexOfMin]->father , VertexArray[IndexOfMin]->distanceToTree ) ;
        InTree[IndexOfMin] = 1 ;//更新新节点状态：在树中
    printf("\nEvery Vertex distance to tree :\n%d %d %d %d %d %d %d %d %d %d %d %d \n", 
    VertexArray[0]->distanceToTree,
    VertexArray[1]->distanceToTree,
    VertexArray[2]->distanceToTree,
    VertexArray[3]->distanceToTree,
    VertexArray[4]->distanceToTree,
    VertexArray[5]->distanceToTree,
    VertexArray[6]->distanceToTree,
    VertexArray[7]->distanceToTree,
    VertexArray[8]->distanceToTree,
    VertexArray[9]->distanceToTree,
    VertexArray[10]->distanceToTree,
    VertexArray[11]->distanceToTree) ;
    printf("Next up to search ----------------> %d \n\n" , IndexOfMin ) ;
    
    }
}


int main()
{
    //printf("%d %d %d %d %d %d %d" , InTree[0], InTree[1], InTree[2], InTree[3], InTree[4], InTree[5], InTree[6]) ;
   //memset( InTree , 0 , 12*sizeof(int) ) ;
   //初始化邻接矩阵 ：
   initializeMatrix() ;
   initializeTreeMatrix() ;

   //添加顶点到‘数组’：
   addVertex('A'); // 0
   addVertex('B'); // 1
   addVertex('C'); // 2
   addVertex('D'); // 3
   addVertex('E'); // 4
   addVertex('F'); // 5
   addVertex('G'); // 6
   addVertex('H'); // 7
   addVertex('I'); // 8
   addVertex('J'); // 9
   addVertex('K'); // 10
   addVertex('L'); // 11

   //添加边 ：
   addEdge( 0, 1 , 20 );    // A - B
   addEdge( 0, 3 , 21 );    // A - D
   addEdge( 1, 2 , 7 );     // B - C
   addEdge( 1, 3 , 13 );    // B - D
   addEdge( 1, 4 , 5 );     // B - E
   addEdge( 2, 4 , 1 );     // C - E
   addEdge( 3, 4 , 10 );    // D - E
   addEdge( 3, 5 , 14 );    // D - F
   addEdge( 4, 5 , 22 );    // E - F
   addEdge( 4, 6 , 15 );    // E - G
   addEdge( 4, 7 , 6 );     // E - H
   addEdge( 5, 6 , 4 );     // F - G
   addEdge( 6, 7 , 11 );    // G - H
   addEdge( 6, 8 , 3 );     // G - I
   addEdge( 6, 9 , 19 );    // G - J
   addEdge( 7, 8 , 2 );     // H - I
   addEdge( 7, 10 , 8 );    // H - K
   addEdge( 7, 11 , 9 );    // H - L
   addEdge( 8, 9 , 18 );    // I - J
   addEdge( 8, 10 , 12 );   // I - K
   addEdge( 9, 10 , 17 );   // J - K
   addEdge( 10, 11 , 16 );  // K - L

   // 打印原来的邻接矩阵
   printf("\nAdjacency Matrix :\n") ;
   printMatrix(0) ;

   // 操作：Prim算法找最小生成树
   PrimAlgorithm(9) ;
   printf("\n\n") ;

   // 打印最小生成树在邻接矩阵上的表示
   printf("\nTree Matrix :\n") ;
   printMatrix(1) ;


   return 0 ;
}
