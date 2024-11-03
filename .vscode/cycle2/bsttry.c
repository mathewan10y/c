#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node;

// Function to create a new node
node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to search for a value `x` and insert it if not found
node *searchAndInsert(node *t, int x)
{
    node *treePointer = t;
    node *tailPointer = NULL;
    int found = 0;

    // Traverse the tree to find the value `x` or the correct insertion point
    while (treePointer != NULL)
    {
        tailPointer = treePointer;

        if (x == treePointer->data)
        {
            found = 1; // Value `x` found in the tree
            printf("Element %d found in the BST.\n", x);
            return t; // No insertion needed; return the unchanged root
        }
        else if (x < treePointer->data)
        {
            treePointer = treePointer->left;
        }
        else
        {
            treePointer = treePointer->right;
        }
    }

    // If the element is not found, insert it at the correct position
    if (!found)
    {
        printf("Element %d not found in the BST. Inserting...\n", x);
        node *newNode = createNode(x);

        if (tailPointer == NULL)
        {                   // If the tree was empty
            return newNode; // Return the new node as the root
        }
        else if (x < tailPointer->data)
        {
            tailPointer->left = newNode;
        }
        else
        {
            tailPointer->right = newNode;
        }
    }
    return t; // Return the (potentially unchanged) root
}

// Helper function to find the inorder successor
node *findMin(node *t)
{
    while (t && t->left != NULL)
    {
        t = t->left;
    }
    return t;
}

// Function to delete a node with value `x` from the BST
node *deleteNode(node *t, int x)
{
    if (t == NULL)
    {
        printf("Element %d not found in the BST.\n", x);
        return t;
    }

    // Traverse the tree to find the node to delete
    if (x < t->data)
    {
        t->left = deleteNode(t->left, x);
    }
    else if (x > t->data)
    {
        t->right = deleteNode(t->right, x);
    }
    else
    {
        // Case 1: Node with no children
        if (t->left == NULL && t->right == NULL)
        {
            free(t);
            t = NULL;
        }
        // Case 2: Node with one child (right or left)
        else if (t->left == NULL)
        {
            node *temp = t;
            t = t->right;
            free(temp);
        }
        else if (t->right == NULL)
        {
            node *temp = t;
            t = t->left;
            free(temp);
        }
        // Case 3: Node with two children
        else
        {
            node *temp = findMin(t->right);              // Find inorder successor
            t->data = temp->data;                        // Copy successor's value to current node
            t->right = deleteNode(t->right, temp->data); // Delete the successor
        }
    }
    return t;
}

// Utility function to perform inorder traversal
void inorderTraversal(node *t)
{
    if (t != NULL)
    {
        inorderTraversal(t->left);
        printf("%d ", t->data);
        inorderTraversal(t->right);
    }
}

int main()
{
    node *t = NULL;
    int choice, x;

    do
    {
        printf("\nMenu:\n");
        printf("1. Insert/Search element\n");
        printf("2. Display inorder traversal\n");
        printf("3. Delete an element\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the element to search/insert: ");
            scanf("%d", &x);
            // Update t with the potentially new root returned by searchAndInsert
            t = searchAndInsert(t, x);
            break;

        case 2:
            printf("Inorder traversal of the BST: ");
            inorderTraversal(t);
            printf("/n");
            display(t, 0);
            printf("\n");
            break;

        case 3:
            printf("Enter the element to delete: ");
            scanf("%d", &x);
            t = deleteNode(t, x); // Update the root after deletion if necessary
            break;

        case 4:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

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

    if (level > 0)
    {
        printf("|-- "); // Indicate connection with vertical bar
    }
    printf("%d\n", node->data);

    // Print left child connection
    display(node->left, level + 1);
}
