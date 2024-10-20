#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Structure for a hash table node
typedef struct Node
{
    char key[100];
    int value;
    struct Node *next;
} Node;

// Structure for the hash table
typedef struct HashTable
{
    Node **table;
} HashTable;

// Function prototypes
HashTable *createHashTable();
unsigned int hash(char *key);
void insert(HashTable *ht, char *key, int value);
int search(HashTable *ht, char *key);
void delete(HashTable *ht, char *key);
void display(HashTable *ht);
void freeHashTable(HashTable *ht);

int main()
{
    HashTable *ht = createHashTable();
    int choice, value;
    char key[100];

    do
    {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key: ");
            scanf("%s", key);
            printf("Enter value: ");
            scanf("%d", &value);
            insert(ht, key, value);
            break;
        case 2:
            printf("Enter key to search: ");
            scanf("%s", key);
            value = search(ht, key);
            if (value != -1)
            {
                printf("Value: %d\n", value);
            }
            else
            {
                printf("Key not found!\n");
            }
            break;
        case 3:
            printf("Enter key to delete: ");
            scanf("%s", key);
            delete (ht, key);
            break;
        case 4:
            display(ht);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    freeHashTable(ht);
    return 0;
}

// Function to create a hash table
HashTable *createHashTable()
{
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    ht->table = (Node **)malloc(TABLE_SIZE * sizeof(Node *));
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ht->table[i] = NULL;
    }
    return ht;
}

// Hash function
unsigned int hash(char *key)
{
    unsigned int hashValue = 0;
    while (*key)
    {
        hashValue = (hashValue << 5) + *key++;
    }
    return hashValue % TABLE_SIZE;
}

// Function to insert a key-value pair into the hash table
void insert(HashTable *ht, char *key, int value)
{
    unsigned int index = hash(key);
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;

    // Insert at the beginning of the linked list
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

// Function to search for a key in the hash table
int search(HashTable *ht, char *key)
{
    unsigned int index = hash(key);
    Node *current = ht->table[index];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Key not found
}

// Function to delete a key-value pair from the hash table
void delete(HashTable *ht, char *key)
{
    unsigned int index = hash(key);
    Node *current = ht->table[index];
    Node *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
            {
                // Deleting the first node in the list
                ht->table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("Key '%s' deleted.\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Key '%s' not found.\n", key);
}

// Function to display the hash table
void display(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *current = ht->table[i];
        if (current != NULL)
        {
            printf("Index %d: ", i);
            while (current != NULL)
            {
                printf(" -> (%s, %d)", current->key, current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}

// Function to free the memory used by the hash table
void freeHashTable(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *current = ht->table[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}
