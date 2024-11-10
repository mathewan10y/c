#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} node;

// Function to create a new tree node
struct TreeNode *createNode(int data)
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to calculate the height of a binary tree
int height(node *root)
{
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to calculate the diameter of a binary tree
int diameter(node *root)
{
    if (root == NULL)
        return 0;

    // Calculate the height of left and right subtrees
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Calculate the diameter of the left and right subtrees
    int leftDiameter = diameter(root->left);
    int rightDiameter = diameter(root->right);

    // Using if-elif conditions to determine the maximum value
    if (leftHeight + rightHeight + 1 > leftDiameter && leftHeight + rightHeight + 1 > rightDiameter)
    {
        return leftHeight + rightHeight + 1; // The diameter passing through root
    }
    else if (leftDiameter > rightDiameter)
    {
        return leftDiameter; // The diameter of the left subtree
    }
    else
    {
        return rightDiameter; // The diameter of the right subtree
    }
}

int main()
{
    // Creating a binary tree
    node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    display(root, 0);
    printf("Diameter of the binary tree: %d\n", diameter(root));

    return 0;
}
void display(node *node, int level)
{
    if (node == NULL)
    {
        return;
    }

    // Print right child first
    display(node->right, level + 1);

    // Print current node value with indentation
    for (int i = 0; i < level; i++)
    {
        printf("    "); // 4 spaces for each level
    }

    // Print the node's value
    if (level > 0)
    {
        printf("|-- "); // Indicate connection with vertical bar
    }
    printf("%d\n", node->data);

    // Print left child connection
    display(node->left, level + 1);
}