#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Helper function to check if a binary tree is a BST
bool isBSTHelper(TreeNode *root, int min, int max)
{
    if (root == NULL)
        return true;

    // If the current node's value is out of the allowed range, return false
    if (root->data <= min || root->data >= max)
        return false;

    // Check the left and right subtrees with updated ranges
    return isBSTHelper(root->left, min, root->data) && isBSTHelper(root->right, root->data, max);
}

// Function to check if the binary tree is a BST
bool isBST(TreeNode *root)
{
    return isBSTHelper(root, INT_MIN, INT_MAX);
}

int main()
{
    // Creating a sample binary tree
    TreeNode *root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(2);
    root->left->right = createNode(8);
    root->right->left = createNode(15);
    root->right->right = createNode(25);

    if (isBST(root))
    {
        printf("The binary tree is a Binary Search Tree (BST).\n");
    }
    else
    {
        printf("The binary tree is not a Binary Search Tree (BST).\n");
    }

    return 0;
}
