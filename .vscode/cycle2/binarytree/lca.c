// least common ancestor
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

// Function to find the Lowest Common Ancestor (LCA)
TreeNode *findLCA(TreeNode *root, int n1, int n2)
{
    if (root == NULL)
        return NULL;

    // If either n1 or n2 matches the root's data, return root
    if (root->data == n1 || root->data == n2)
        return root;

    // Recur for left and right subtrees
    TreeNode *leftLCA = findLCA(root->left, n1, n2);
    TreeNode *rightLCA = findLCA(root->right, n1, n2);

    // If both left and right LCA are non-NULL, then root is the LCA
    if (leftLCA && rightLCA)
        return root;

    // Otherwise, return the non-NULL child (either left or right)
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

int main()
{
    // Creating a sample binary tree
    TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int n1 = 4, n2 = 5;
    TreeNode *lca = findLCA(root, n1, n2);

    if (lca != NULL)
    {
        printf("The Lowest Common Ancestor of nodes %d and %d is: %d\n", n1, n2, lca->data);
    }
    else
    {
        printf("No common ancestor found.\n");
    }

    return 0;
}
