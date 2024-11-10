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

// Function to perform level-order traversal
void levelOrderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;

    struct TreeNode *queue[100]; // Queue for level-order traversal
    int front = 0, rear = 0;

    // Enqueue the root
    queue[rear++] = root;

    while (front < rear)
    {
        // Dequeue the front element
        struct TreeNode *current = queue[front++];
        printf("%d ", current->data);

        // Enqueue the left child if it exists
        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }

        // Enqueue the right child if it exists
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
}

int main()
{
    // Creating a binary tree
    struct TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Level-order Traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    return 0;
}
