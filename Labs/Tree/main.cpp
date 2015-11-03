#include <stdio.h>
#include <stdlib.h>

/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct node
{
    int data;
    struct node* left;
    struct node* right;
};

int countOnlys(node* r)
{
    if(r == NULL || (r->left == NULL && r->right == NULL))
    {
        return 0;
    }
    if(r->left != NULL && r->right != NULL)
    {
        return countOnlys(r->left) + countOnlys(r->right);
    }
    else
    {
        return 1 + countOnlys(r->left) + countOnlys(r->right);
    }

    return 0;
}

int countNoChildren(node* r)
{
    if(r == NULL)
    {
        return 0;
    }
    if(r->left == NULL && r->right == NULL)
    {
        return 1;
    }
    else
    {
        return countNoChildren(r->left) + countNoChildren(r->right);
    }
    return 0;
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newNode(int data)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return(node);
}

/*Driver program to test above functions*/
int main()
{
    /*create a tree*/
    struct node *root = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    //root->right->right       = newNode(6);
    root->right->left       = newNode(7);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);

    /*get leaf count of the above created tree*/
    printf("Leaf count of the tree is %d", countOnlys(root ));

    getchar();
    return 0;
}
