#include <stdio.h>
#include <stdlib.h>

// Define a node structure for the queue
typedef struct Node
{
    int data;
    struct Node *next;
} node;

node *front = NULL; // Pointer to the front of the queue
node *rear = NULL;  // Pointer to the rear of the queue

// Function to enqueue an element onto the queue
void enqueue(int data)
{
    node *c = (node *)malloc(sizeof(node));

    c->data = data;
    c->next = NULL;

    if (front == NULL) // Queue is empty
    {
        front = rear = c;
    }
    else // Queue is not empty
    {
        rear->next = c;
        rear = c;
    }
    printf("%d enqueued onto queue.\n", data);
}

// Function to dequeue an element from the queue
void dequeue()
{
    if (front == NULL)
    {
        printf("Queue underflow! Cannot dequeue from an empty queue.\n");
    }
    else
    {
        node *c = front;
        printf("%d is dequeued\n", front->data);
        front = front->next;

        free(c);
    }
}

// Function to display the queue
void display()
{
    if (front == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }
    else
    {
        node *p = front;
        printf("Queue elements: ");

        while (p != NULL)
        {
            printf("%d ", p->data);
            p = p->next;
        }
        printf("\n");
    }
}

// Main program to demonstrate queue operations
int main()
{
    int choice, value;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Choose an option (1-4): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter a value to enqueue: ");
            scanf("%d", &value);
            enqueue(value);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
            break;
        case 4:
            printf("Exiting program.\n");
            // Free the allocated queue memory
            while (front != NULL)
            {
                dequeue();
            }
            exit(0);
            break;
        default:
            printf("Invalid choice! Please choose again.\n");
            continue;
        }
    }
}
