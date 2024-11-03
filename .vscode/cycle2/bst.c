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
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a value into the BST
Node *insert(Node *node, int value)
{
    if (node == NULL)
    {
        return createNode(value);
    }

    if (value < node->value)
    {
        node->left = insert(node->left, value); // Insert into the left subtree
    }
    else if (value > node->value)
    {
        node->right = insert(node->right, value); // Insert into the right subtree
    }
    // If value already exists, do nothing (no duplicates)

    return node;
}

// Function to display the binary search tree
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

// Function to free the binary search tree
void freeTree(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    freeTree(node->left);  // Free left subtree
    freeTree(node->right); // Free right subtree
    free(node);            // Free the current node
}

int main()
{
    // Binary Search Tree
    Node *bstRoot = NULL;
    int value;
    char choice;

    printf("Insert values into the Binary Search Tree:\n");
    do
    {
        printf("Enter a value: ");
        scanf("%d", &value);
        bstRoot = insert(bstRoot, value); // Insert value into the BST

        printf("Do you want to insert another value? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');

    printf("\nDisplaying Binary Search Tree:\n");
    display(bstRoot, 0);

    printf("\nIn-Order Traversal of Binary Search Tree:\n");
    inOrder(bstRoot);
    printf("\n");

    printf("Pre-Order Traversal of Binary Search Tree:\n");
    preOrder(bstRoot);
    printf("\n");

    printf("Post-Order Traversal of Binary Search Tree:\n");
    postOrder(bstRoot);
    printf("\n");

    // Free allocated memory
    freeTree(bstRoot);

    return 0;
}
