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

// Function to find the minimum depth of the binary tree
int minDepth(TreeNode *root)
{
    if (root == NULL)
        return 0;

    // If left subtree is NULL, only consider the right subtree
    if (root->left == NULL)
        return minDepth(root->right) + 1;

    // If right subtree is NULL, only consider the left subtree
    if (root->right == NULL)
        return minDepth(root->left) + 1;

    // If both subtrees are non-empty, take the minimum depth of the two
    int leftDepth = minDepth(root->left);
    int rightDepth = minDepth(root->right);
    return (leftDepth < rightDepth ? leftDepth : rightDepth) + 1;
}

int main()
{
    // Creating a sample binary tree
    TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->left->right->left = createNode(6);

    printf("The minimum depth of the binary tree is: %d\n", minDepth(root));

    return 0;
}
