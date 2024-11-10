#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new tree node
struct TreeNode *createNode(int data)
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to calculate the height of a binary tree
int height(struct TreeNode *root)
{
    if (root == NULL)
    {
        return -1; // Height of an empty tree is -1
    }

    // Recursively calculate the height of left and right subtrees
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Return the maximum of the left and right subtree heights plus 1 for the current node
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int main()
{
    // Creating a binary tree
    struct TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Height of the binary tree: %d\n", height(root));

    return 0;
}
