#include <stdio.h>
#include <stdlib.h>

// Define the structure for the node
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Function to create a new node
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to print the linked list
void printList(Node *head)
{
    while (head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Function to partition the linked list around the pivot node
Node *partition(Node *head, Node *end, Node **newHead, Node **newEnd)
{
    Node *pivot = end;
    Node *prev = NULL;
    Node *curr = head;
    Node *tail = pivot;

    // Traverse the list and reorder the nodes based on pivot
    while (curr != pivot)
    {
        if (curr->data < pivot->data)
        {
            if (*newHead == NULL)
                *newHead = curr;
            prev = curr;
            curr = curr->next;
        }
        else
        {
            if (prev)
                prev->next = curr->next;
            Node *temp = curr->next;
            curr->next = NULL;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    // Adjust the newEnd pointer
    if (*newHead == NULL)
        *newHead = pivot;
    *newEnd = tail;

    return pivot;
}

// Function to perform QuickSort on the linked list
Node *quickSortRecur(Node *head, Node *end)
{
    if (!head || head == end)
        return head;

    Node *newHead = NULL;
    Node *newEnd = NULL;

    // Partition the list around the pivot
    Node *pivot = partition(head, end, &newHead, &newEnd);

    // Recursively sort the left part
    if (newHead != pivot)
    {
        Node *temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;

        newHead = quickSortRecur(newHead, temp);

        // Connect the left part to the pivot
        temp = newHead;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = pivot;
    }

    // Recursively sort the right part
    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

// Function to sort the linked list using QuickSort
void quickSort(Node **headRef)
{
    *headRef = quickSortRecur(*headRef, *headRef);
}

int main()
{
    Node *head = createNode(5);
    head->next = createNode(3);
    head->next->next = createNode(8);
    head->next->next->next = createNode(1);
    head->next->next->next->next = createNode(7);

    printf("Original List: ");
    printList(head);

    quickSort(&head);

    printf("Sorted List: ");
    printList(head);

    return 0;
}
