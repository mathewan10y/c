#include <stdio.h>
#include <stdlib.h>
g
    // Definition for a binary tree node
    typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new tree node
TreeNode *createTreeNode(int data)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to print nodes at distance k from the given node
void printSubtreeAtDistanceK(TreeNode *root, int k)
{
    if (root == NULL || k < 0)
        return;
    if (k == 0)
    {
        printf("%d ", root->data); // Print the node if it's at distance 0
        return;
    }
    printSubtreeAtDistanceK(root->left, k - 1);
    printSubtreeAtDistanceK(root->right, k - 1);
}

// Function to find and print nodes at distance k from the given target node
int printNodesAtDistanceK(TreeNode *root, TreeNode *target, int k)
{
    if (root == NULL)
        return -1;

    // If the root is the target node, print nodes at distance k
    if (root == target)
    {
        printSubtreeAtDistanceK(root, k);
        return 0;
    }

    // Recursively search for the target node in the left and right subtrees
    int leftDistance = printNodesAtDistanceK(root->left, target, k);
    if (leftDistance != -1)
    {
        // If the target is in the left subtree, print the right subtree at distance (k - leftDistance - 2)
        if (leftDistance + 1 == k)
            printf("%d ", root->data);
        printSubtreeAtDistanceK(root->right, k - leftDistance - 2);
        return leftDistance + 1;
    }

    int rightDistance = printNodesAtDistanceK(root->right, target, k);
    if (rightDistance != -1)
    {
        // If the target is in the right subtree, print the left subtree at distance (k - rightDistance - 2)
        if (rightDistance + 1 == k)
            printf("%d ", root->data);
        printSubtreeAtDistanceK(root->left, k - rightDistance - 2);
        return rightDistance + 1;
    }

    return -1; // Return -1 if the target is not found in this subtree
}

int main()
{
    // Creating a sample tree
    TreeNode *root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    TreeNode *target = root->left; // Target node is 2
    int k = 2;                     // Distance k

    printf("Nodes at distance %d from node %d are: ", k, target->data);
    printNodesAtDistanceK(root, target, k);
    printf("\n");

    return 0;
}
