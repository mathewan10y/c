#include <stdio.h>
#include <stdlib.h>

// Define the structure of a linked list node
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

// Function to merge two sorted linked lists
Node *mergeSortedLists(Node *list1, Node *list2)
{
    Node *dummy = createNode(0); // Dummy node to simplify handling the head
    Node *tail = dummy;          // Tail points to the last node of the merged list

    // Traverse both lists and merge them
    while (list1 != NULL && list2 != NULL)
    {
        if (list1->data < list2->data)
        {
            tail->next = list1;  // Add list1 node to the merged list
            list1 = list1->next; // Move list1 pointer
        }
        else
        {
            tail->next = list2;  // Add list2 node to the merged list
            list2 = list2->next; // Move list2 pointer
        }
        tail = tail->next; // Move tail pointer
    }

    // If there are any remaining nodes in list1, attach them
    if (list1 != NULL)
    {
        tail->next = list1;
    }
    // If there are any remaining nodes in list2, attach them
    if (list2 != NULL)
    {
        tail->next = list2;
    }

    // Return the merged list, which starts after the dummy node
    return dummy->next;
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

// Main function to test merging of two sorted lists
int main()
{
    // Creating first sorted list: 1 -> 3 -> 5
    Node *list1 = createNode(1);
    list1->next = createNode(3);
    list1->next->next = createNode(5);

    // Creating second sorted list: 2 -> 4 -> 6
    Node *list2 = createNode(2);
    list2->next = createNode(4);
    list2->next->next = createNode(6);

    // Merging the two sorted lists
    Node *mergedList = mergeSortedLists(list1, list2);

    // Print the merged list
    printf("Merged List: ");
    printList(mergedList);

    return 0;
}
