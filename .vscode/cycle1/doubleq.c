#include <stdio.h>
#include <stdlib.h>

int deque[10];
int front = -1, rear = -1, element;

void insertFront(int n)
{
    if ((front == 0 && rear == n - 1) || (front == rear + 1))
    {
        printf("Deque is full.\n");
        return;
    }
    else
    {
        if (front == -1)
        { // Empty deque
            front = rear = 0;
        }
        else if (front == 0)
        {
            front = n - 1;
        }
        else
        {
            front--;
        }

        printf("Enter the element to insert at front: ");
        scanf("%d", &element);
        deque[front] = element;
    }
}

// Function to insert an element at the rear end
void insertRear(int n)
{
    if ((front == 0 && rear == n - 1) || (front == rear + 1))
    {
        printf("Deque is full.\n");
        return;
    }
    else
    {
        if (rear == -1)
        { // Empty deque
            front = rear = 0;
        }
        else if (rear == n - 1)
        {
            rear = 0;
        }
        else
        {
            rear++;
        }
    }
    printf("Enter the element to insert at front: ");
    scanf("%d", &element);
    deque[rear] = element;
}

// Function to delete an element from the front end
void deleteFront(int n)
{
    if (front == -1)
    {
        printf("Deque is empty.\n");
        return;
    }

    printf("Deleted element: %d at position %d\n", deque[front], front);

    if (front == rear)
    { // Only one element was in the deque
        front = rear = -1;
    }
    else if (front == n - 1)
    {
        front = 0;
    }
    else
    {
        front++;
    }
}

// Function to delete an element from the rear end
void deleteRear(int n)
{
    if (front == -1)
    {
        printf("Deque is empty.\n");
        return;
    }

    printf("Deleted element: %d\n", deque[rear]);

    if (front == rear)
    { // Only one element was in the deque
        front = rear = -1;
    }
    else if (rear == 0)
    {
        rear = n - 1;
    }
    else
    {
        rear--;
    }
}

// Function to display the elements of the deque
void display(int n)
{
    int i = front;
    if (front == -1)
    {
        printf("Deque is empty.\n");
        return;
    }

    printf("Deque elements:\n");

    while (i != rear)
    {
        printf("%d at index %d \n", deque[i], i);
        i = (i + 1) % n;
    }
    printf("%d at index %d \n", deque[i], i);
}

int main()
{
    int choice, element, n;
    printf("enter number of elements in array:");
    scanf("%d", &n);
    while (1)
    {
        printf("\n** DEQUE MENU **\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Delete from Front\n");
        printf("4. Delete from Rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            insertFront(n);
            break;
        case 2:

            insertRear(n);
            break;
        case 3:
            deleteFront(n);
            break;
        case 4:
            deleteRear(n);
            break;
        case 5:
            display(n);
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}