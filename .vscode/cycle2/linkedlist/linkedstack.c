#include <stdio.h>
#include <stdlib.h>

// Define a node structure for the stack
typedef struct Node
{
    int data;
    struct Node *next;
} node;

node *top = NULL;
// Function to push an element onto the stack
void push(int data)
{
    node *c;
    c = (node *)malloc(sizeof(node));
    c->data = data;
    if (top == NULL)
    {
        c->next = NULL;
        top = c;
    }
    else
    {
        c->next = top;
        top = c;
    }
    printf("%d pushed onto stack.\n", data);
}

// Function to pop an element from the stack
void pop()
{
    if (top == NULL)
    {
        printf("Stack underflow! Cannot pop from an empty stack.\n");
    }
    else
    {
        node *c = top;
        printf("%d is deleted", top->data);
        top = top->next;
        free(c);
    }
}

// Function to display the stack
void display()
{
    if (top == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }
    else
    {
        node *p = top;
        printf("Stack elements: ");
        while (p != NULL)
        {
            printf("%d ", p->data);
            p = p->next;
        }
        printf("\n");
    }
}

// Main program to demonstrate stack operations
void main()
{
    int choice, value;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Choose an option (1-4): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter a value to push: ");
            scanf("%d", &value);
            push(value);
            break;
        case 2:
            pop();
            break;
        case 3:
            display();
            break;
        case 4:
            printf("Exiting program.\n");
            // Free the allocated stack memory
            exit(0);
            break;
        default:
            printf("Invalid choice! Please choose again.\n");
            continue;
        }
    }
}
