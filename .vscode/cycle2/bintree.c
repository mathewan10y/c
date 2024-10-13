#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node
Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to populate the binary tree
Node *populate()
{
    int value;
    char choice;

    printf("Enter the value for the node: ");
    scanf("%d", &value);
    Node *node = createNode(value);

    printf("Do you want to enter left of %d? (y/n): ", value);
    scanf(" %c", &choice);
    if (choice == 'y')
    {
        node->left = populate(); // Assign left child
    }

    printf("Do you want to enter right of %d? (y/n): ", value);
    scanf(" %c", &choice);
    if (choice == 'y')
    {
        node->right = populate(); // Assign right child
    }

    return node; // Return the created node
}

// Function to display the binary tree with connections
void display(Node *node, int level)
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
    printf("%d\n", node->value);

    // Print left child connection
    display(node->left, level + 1);
}

// In-order traversal
void inOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    inOrder(node->left);        // Visit left subtree
    printf("%d ", node->value); // Visit node
    inOrder(node->right);       // Visit right subtree
}

// Pre-order traversal
void preOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("%d ", node->value); // Visit node
    preOrder(node->left);       // Visit left subtree
    preOrder(node->right);      // Visit right subtree
}

// Post-order traversal
void postOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    postOrder(node->left);      // Visit left subtree
    postOrder(node->right);     // Visit right subtree
    printf("%d ", node->value); // Visit node
}

int main()
{
    // Binary Tree
    Node *binaryTreeRoot = NULL;
    printf("Populate the Binary Tree:\n");
    binaryTreeRoot = populate(); // Directly assign the root

    printf("\nDisplaying Binary Tree:\n");
    display(binaryTreeRoot, 0);

    printf("\nIn-Order Traversal of Binary Tree:\n");
    inOrder(binaryTreeRoot);
    printf("\n");

    printf("Pre-Order Traversal of Binary Tree:\n");
    preOrder(binaryTreeRoot);
    printf("\n");

    printf("Post-Order Traversal of Binary Tree:\n");
    postOrder(binaryTreeRoot);
    printf("\n");

    // Free allocated memory (not implemented in this example)
    // Ideally, you should free the nodes in the tree.

    return 0;
}
