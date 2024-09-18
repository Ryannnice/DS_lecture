/*
 * AVL tree algorithms in C
 * Author: Qinbing Fu
 * Date: Apr 2023
 */
 
#include<stdio.h>
#include<stdlib.h>


// structure of tree node
struct node
{
    int data;
    struct node* left;
    struct node* right;
    // height of node
    int ht;
};
 
// initializing root node as global variable
struct node* root = NULL;
 
// functions prototyping
struct node* create(int);
struct node* insert(struct node*, int);
struct node* delete(struct node*, int);
struct node* search(struct node*, int);
struct node* rotate_left(struct node*);
struct node* rotate_right(struct node*);
int balance_factor(struct node*);
int height(struct node*);
void inorder(struct node*);
void preorder(struct node*);
void postorder(struct node*);
void selection(void);

// entry function 
int main()
{
    // comment it and create your own code after selection()
    selection();
 
    return 0;
}
 
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
struct node* insert(struct node* root, int data)
{
    if (root == NULL)
    {
        struct node* new_node = create(data) ;
        if (new_node == NULL)
        {
            return NULL ;
        }
        root = new_node ; // finally end here.
    }
    else if (data > root->data)
    {
        // inserting the new node to the right
        root->right = insert(root->right, data);
 
        // if tree is unbalanced, then rotate it to fix the issue
        if (balance_factor(root) == -2)
        {
            if (data > root->right->data)
            {
                root = rotate_left(root);
            }
            else
            {
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    }
    else
    {
        // inserting the new node to the left
        root->left = insert(root->left, data);
 
        // if tree is unbalanced, then rotate it to fix the issue
        if (balance_factor(root) == 2)
        {
            if (data < root->left->data)
            {
                root = rotate_right(root);
            }
            else // left-right_case
            {
                root->left = rotate_left(root->left); ////////////
                root = rotate_right(root);
            }
        }
    }
    // updating the heights of the nodes
    root->ht = height(root);

    return root;
}
 
// deleting a node from the AVL tree
struct node * delete(struct node *root, int x)
{
    struct node * temp = NULL;
 
    if (root == NULL)
    {
        return NULL;
    } 
 
    if (x > root->data)
    {
        root->right = delete(root->right, x);

        // if tree is unbalanced, then rotate it to fix the issue
        if (balance_factor(root) == 2)
        {
            if (balance_factor(root->left) >= 0)
            {
                root = rotate_right(root);
            }
            else
            {
                root->left = rotate_left(root->left); 
                root = rotate_right(root);
            }
        }
    }
    else if (x < root->data)
    {
        root->left = delete(root->left, x);

        // if tree is unbalanced, then rotate it to fix the issue
        if (balance_factor(root) == -2)
        {
            if (balance_factor(root->right) <= 0)
            {
                root = rotate_left(root);
            }
            else
            {
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    }
    else
    {
        if (root->right != NULL)
        { 
            temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
 
            root->data = temp->data;
            root->right = delete(root->right, temp->data);

            // if tree is unbalanced, then rotate it to fix the issue
            if (balance_factor(root) == 2)
            {
                if (balance_factor(root->left) >= 0)
                {
                    root = rotate_right(root);
                }
                else
                {
                    root->left = rotate_left(root->left);
                    root = rotate_right(root);
                }
            }
        }
        else
        {
            return (root->left);
        }
    }
    root->ht = height(root);

    return (root);
}
 
// searching a node in the AVL tree
struct node* search(struct node* root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
 
    if(root->data == key)
    {
        return root;
    }
 
    if(key > root->data)
    {
        search(root->right, key);
    }
    else
    {
        search(root->left, key);
    } 
}
 
// inorder traversal of the tree
void inorder(struct node* root)
{
    if (root == NULL)
    {
        return ;
    }
 
    inorder(root->left) ;
    printf("%d ", root->data) ;
    inorder(root->right) ;
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
 
// postorder traversal of the tree
void postorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// selection of multiple operations on AVL tree
void selection(void)
{
    int user_choice, data;
    char user_continue = 'y';
    struct node* result = NULL;
 
    while (user_continue == 'y')
    {
        printf("\n\n------- AVL TREE --------\n");
        printf("\n1. Insert");
        printf("\n2. Delete");
        printf("\n3. Search");
        printf("\n\n4. Inorder");
        printf("\n5. Preorder");
        printf("\n6. Postorder");
        printf("\n\n7. Exit program");
 
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &user_choice);
 
        switch(user_choice)
        {
            case 1:
                printf("\nEnter data: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
 
            case 2:
                printf("\nEnter data: ");
                scanf("%d", &data);
                root = delete(root, data);
                break;
 
            case 3:
                printf("\nEnter data: ");
                scanf("%d", &data);
                result = search(root, data);
                if (result == NULL)
                {
                    printf("\nNode not found!");
                }
                else
                {
                    printf("\nNode found");
                }
                break;
            case 4:
                inorder(root);
                break;
 
            case 5:
                preorder(root);
                break;
 
            case 6:
                postorder(root);
                break;
 
            case 7:
                printf("\n\tProgram terminated\n");
                return;
 
            default:
                printf("\n\tInvalid choice ! ");
        }
 
        printf("\n\nDo you want to continue? ");
        scanf(" %c", &user_continue);
    }
}

