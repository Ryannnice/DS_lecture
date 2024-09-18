/*
 * AVL tree algorithms put to use in Hash_Table data structure.
 * Author: Qinbing Fu , Renyvan Liu.
 * Date: May 2023
 */
 
#include<stdio.h>
#include<stdlib.h>


unsigned int hash( unsigned int n )
{
    return n % 10 ;
}

// structure of tree node
typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
    // height of node
    int ht;
}node ;
 
// functions prototyping
struct node* create(int);
struct node* insert(struct node**, int);
struct node* rotate_left(struct node*);
struct node* rotate_right(struct node*);
int balance_factor(struct node*);
int height(struct node*);
void preorder(struct node*);


// creating a new node of tree
struct node* create(int data)
{
    struct node* new_node = (struct node*)malloc (sizeof(struct node ) );
 
    // memory error handled
    if (new_node == NULL){
        printf("\nMemory can't be allocated\n");
        return NULL;
    }
    // initialize :
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
 
// rotating to the left
struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // updating the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);
 
    // return root after rotation
    return right_child ; // 
}
 
// rotating to the right
struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // updating the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);
 
    // return the new node after rotation
    return left_child;
}
 
// calculating the balance factor of a node
int balance_factor(struct node* root)
{
    // return root->left->ht - root->right->ht ;
   
    int lh, rh;
    if (root == NULL)
        return 0;

    // left height :
    if (root->left == NULL){
        lh = 0;
    }else{
        lh = 1 + root->left->ht;
    }
    // right height :
    if (root->right == NULL){
        rh = 0;
    }else{
        rh = 1 + root->right->ht;
    }

    // calculate balance_factor :
    return lh - rh;
}
 
// calculating the height of the node
int height(struct node* root)
{
    int lh, rh;
    if (root == NULL) 
        return 0;

    // recurtion --> left_height
    if (root->left == NULL){
        lh = 0;
    }else{
        lh = 1 + root->left->ht;
    }
    // recurtion --> right_height
    if (root->right == NULL){
        rh = 0;
    }else{
        rh = 1 + root->right->ht;
    } 

    // return Max( lh , rh ) :
    return lh>rh ? lh : rh ;

}
 
// inserting a new node in the AVL tree
struct node* insert(struct node** root, int data)
{
    if (*root == NULL)
    {
        struct node* new_node = create(data);
        if (new_node == NULL)
        {
            return NULL;
        }
        *root = new_node;
    }
    else if (data > (*root)->data)
    {
        // inserting the new node to the right
        (*root)->right = insert( &((*root)->right) , data);
 
        // if tree is unbalanced, then rotate it to fix the issue
        if (balance_factor(*root) == -2)
        {
            if (data > (*root)->right->data)
            {
                *root = rotate_left(*root);
            }
            else
            {
                (*root)->right = rotate_right((*root)->right);
                *root = rotate_left(*root);
            }
        }
    }
    else
    {
        // inserting the new node to the left
        (*root)->left = insert( &((*root)->left) , data );
 
        // if tree is unbalanced, then rotate it to fix the issue
        if (balance_factor(*root) == 2)
        {
            if (data < (*root)->left->data)
            {
                *root = rotate_right(*root);
            }
            else // left-right_case
            {
                (*root)->left = rotate_left((*root)->left); ////////////
                *root = rotate_right(*root);
            }
        }
    }
    // updating the heights of the nodes
    (*root)->ht = height(*root);

    return *root;
}

// preorder traversal of the tree
void preorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
 
int main()
{  
    int arr[15] =
  { 534, 415, 465, 459, 869, 
    442, 840, 180, 450, 265,
    23 , 946, 657,  3 , 29  };

    // initialize table : 
    node* root_table[10] ;
    for( int i = 0 ; i < 10 ; i++ )
    {
        root_table[i] = NULL;
    }

    // payload : 
    printf("\n\nPayload : \n\n") ;
    for( int i = 0 ; i < 15 ; i++ )
    {
        insert( &(root_table[ hash(arr[i]) ] ) , arr[i] ) ;
        printf("'%d' inserted successfully\n", arr[i]) ;
    }

    // traversal : 
    printf("\n\nTraversal : \n\n") ;
    for (int i = 0; i < 10; i++)
    {
        printf("Element in '%d' index (pre_order_traversal) : ", i);
        preorder(root_table[i]) ;
        printf("\n") ;
    }



    printf("\n\nDemostration over...\n ") ;
}
