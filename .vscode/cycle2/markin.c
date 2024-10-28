#include <stdio.h>
#include <stdlib.h>

// Define the Node structure for a doubly linked list
typedef struct Node
{
    int data;           // Atomic data
    struct Node *dlink; // Pointer to the previous node (dlink)
    struct Node *rlink; // Pointer to the next node (rlink)
    int mark;           // Mark flag (0: unmarked, 1: marked, -1: not tagged)
    int tag;            // Additional flag for conditions
} Node;

// Define the Node structure for the stack
typedef struct StackNode
{
    Node *linkedNode; // Pointer to a Node in the doubly linked list
} StackNode;

// Global stack variables
StackNode *stack[100]; // Stack array to hold nodes
int top = -1;          // Initialize top to -1, indicating an empty stack

// Function to create a new node for the doubly linked list
Node *createNode(int data, int tag)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->rlink = NULL; // Initialize rlink
    newNode->dlink = NULL; // Initialize dlink
    newNode->mark = 0;     // Initially unmarked
    newNode->tag = tag;    // Set the tag
    return newNode;
}

// Function to push a node onto the stack
void push(Node *node)
{
    if (top >= 99)
    { // Check for stack overflow
        printf("Stack overflow! Cannot push more nodes.\n");
        return;
    }
    top++; // Increment top
    stack[top] = (StackNode *)malloc(sizeof(StackNode));
    stack[top]->linkedNode = node;
    printf("Pushed node with data: %d onto the stack.\n", node->data);
}

// Function to pop a node from the stack
Node *pop()
{
    if (top < 0)
    { // Check for stack underflow
        printf("Stack underflow! Cannot pop from an empty stack.\n");
        return NULL;
    }
    else
    {
        Node *poppedNode = stack[top]->linkedNode;
        free(stack[top]); // Free the stack node
        top--;            // Decrement top
        printf("Popped node with data: %d from the stack.\n", poppedNode->data);
        return poppedNode;
    }
}

// Function to process nodes based on conditions
void processNodes(Node *head)
{
    // Initialize the stack
    top = -1; // Set top = -1 to indicate empty stack

    // Push the head node onto the stack
    push(head);

    while (top >= 0)
    {                    // While stack is not empty
        Node *p = pop(); // Pop the top node

        // Check if the popped node is valid
        if (p == NULL)
            continue;

        Node *q = p->rlink; // Set q to p's rlink

        // Check if q is not null, q's tag is set, and q is not marked
        if (q != NULL && q->tag && !q->mark)
        {
            push(q);     // Push q onto the stack
            q->mark = 1; // Mark q
        }

        // After processing q, check the current node p
        p = p->dlink; // Move to the previous node
        if (p != NULL)
        {
            if (!p->tag)
            {
                p->mark = -1; // Mark as -1 if tag is not set
            }
            else
            {
                push(p); // Push onto the stack if tag is set
            }
        }
    }
}

// Function to display the nodes in the list
void display(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("Data: %d, Marked: %d, Tag: %d\n", current->data, current->mark, current->tag);
        current = current->rlink; // Move to the next node
    }
}

// Main function
int main()
{
    // Create a doubly linked list
    Node *head = createNode(1, 1);
    Node *second = createNode(2, 1);
    Node *third = createNode(3, 0); // Third node has tag 0
    Node *fourth = createNode(4, 1);

    // Link the nodes
    head->rlink = second;
    second->dlink = head;
    second->rlink = third;
    third->dlink = second;
    third->rlink = fourth;
    fourth->dlink = third;

    // Process nodes starting from head
    printf("Processing nodes:\n");
    processNodes(head);

    // Display the list after processing
    printf("\nList after processing:\n");
    display(head);

    // Free allocated memory (not shown here for simplicity)
    // Ideally, you would implement a free function to clean up the list and stack

    return 0;
}
