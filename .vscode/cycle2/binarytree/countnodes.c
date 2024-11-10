#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node with typedef
typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new tree node
TreeNode *createNode(int data)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to calculate the number of nodes in the binary tree
int countNodes(TreeNode *root)
{
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main()
{
    // Creating a sample binary tree
    TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("The number of nodes in the binary tree is: %d\n", countNodes(root));

    return 0;
}