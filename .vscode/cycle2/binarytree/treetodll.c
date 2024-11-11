#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Definition for a doubly linked list node
typedef struct DLLNode
{
    int data;
    struct DLLNode *prev;
    struct DLLNode *next;
} DLLNode;

// Function to create a new tree node
TreeNode *createTreeNode(int data)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a new doubly linked list node
DLLNode *createDLLNode(int data)
{
    DLLNode *newNode = (DLLNode *)malloc(sizeof(DLLNode));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Helper function to perform in-order traversal and convert BST to DLL
void inorderBSTtoDLL(TreeNode *root, DLLNode **head, DLLNode **prev)
{
    if (root == NULL)
        return;

    // Traverse the left subtree
    inorderBSTtoDLL(root->left, head, prev);

    // Create a new DLL node for the current tree node
    DLLNode *newNode = createDLLNode(root->data);

    // If the DLL is empty, set head to the new node
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        // Link the previous DLL node to the current node
        (*prev)->next = newNode;
        newNode->prev = *prev;
    }

    // Update the previous pointer
    *prev = newNode;

    // Traverse the right subtree
    inorderBSTtoDLL(root->right, head, prev);
}

// Function to convert a BST to a doubly linked list
DLLNode *BSTtoDLL(TreeNode *root)
{
    DLLNode *head = NULL;
    DLLNode *prev = NULL;
    inorderBSTtoDLL(root, &head, &prev);
    return head;
}

// Function to print the doubly linked list
void printDLL(DLLNode *head)
{
    DLLNode *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    // Creating a sample BST
    TreeNode *root = createTreeNode(4);
    root->left = createTreeNode(2);
    root->right = createTreeNode(6);
    root->left->left = createTreeNode(1);
    root->left->right = createTreeNode(3);
    root->right->left = createTreeNode(5);
    root->right->right = createTreeNode(7);

    // Convert BST to Doubly Linked List
    DLLNode *head = BSTtoDLL(root);

    // Print the doubly linked list
    printf("Doubly Linked List: ");
    printDLL(head);

    return 0;
}
