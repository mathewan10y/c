#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define the structure for a doubly linked list node
typedef struct Node
{
    char data;
    struct Node *next;
    struct Node *prev;
} node;

// Global variables for the head and tail of the doubly linked list
node *head = NULL;
node *tail = NULL;

// Function to create a new node
node *createNode(char data)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to create a doubly linked list from a string
void createDoublyLinkedList(char *str)
{
    // Traverse the string and create nodes
    for (int i = 0; str[i] != '\0'; i++)
    {
        node *newNode = createNode(str[i]);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode; // Tail points to the only node
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode; // Update tail to the new last node
        }
    }
}

// Function to check if the string is a palindrome using the doubly linked list
bool isPalindrome()
{

    node *left = head;
    node *right = tail;

    // Compare characters from both ends
    while (left != right && left != right->prev)
    {
        if (left->data != right->data)
        {
            return false; // Mismatch found, not a palindrome
        }
        left = left->next;
        right = right->prev;
    }
    return true;
}

int main()
{
    char str[100]; // Declare a buffer for the input string

    // Get the string input from the user
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove the newline character if present
    str[strcspn(str, "\n")] = '\0';

    // Create a doubly linked list from the input string
    createDoublyLinkedList(str);

    // Check if the string is a palindrome
    if (head == NULL)
    {
        printf("string empty");
    }
    else
    {
        if (isPalindrome())
        {
            printf("The string \"%s\" is a palindrome.\n", str);
        }
        else
        {
            printf("The string \"%s\" is not a palindrome.\n", str);
        }
    }

    // Free the list nodes after use
    node *current = head;
    while (current != NULL)
    {
        node *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}