#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Include limits.h for INT_MAX

// Define a node structure for the polynomial
typedef struct Node
{
    int coefficient;
    int exponent;
    struct Node *next;
} polytype; // Alias for Node

// Function to create a new polynomial term
polytype *createNode(int coefficient, int exponent)
{
    polytype *newNode = (polytype *)malloc(sizeof(polytype));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term into the polynomial
polytype *insertTerm(int coefficient, int exponent, polytype *tail)
{
    polytype *temp = createNode(coefficient, exponent);
    temp->next = tail->next;
    tail->next = temp;
    return temp;
}

void polyprod(polytype *a, polytype *b)
{
    polytype *result = createNode(0, INT_MAX); // Dummy head for result
    polytype *tail = result;                   // Initialize tail

    for (polytype *ap = a; ap != NULL; ap = ap->next)
    {
        for (polytype *bp = b; bp != NULL; bp = bp->next)
        {
            int tcoeff = ap->coefficient * bp->coefficient;
            int texp = ap->exponent + bp->exponent;

            // Find the appropriate position for the new term
            tail = result;
            while (tail->next != NULL && tail->exponent > texp)
            {
                if ((tail->next)->exponent >= texp)
                    tail = tail->next;
                else
                    break;
            }
            if (tail->exponent == texp)
                tail->coefficient = tail->coefficient + tcoeff;
            else if (tail->exponent > texp)
                tail = insertTerm(tcoeff, texp, tail);
        }
    }

    // Skip the dummy head
    tail = result;
    result = result->next;
    free(tail);

    display(result);
}

// Function to display the polynomial
void display(polytype *head)
{
    if (head == NULL)
    {
        printf("0\n");
        return;
    }
    polytype *current = head;
    while (current != NULL)
    {
        printf("%dx^%d", current->coefficient, current->exponent);
        if (current->next != NULL)
        {
            printf(" + ");
        }
        current = current->next;
    }
    printf("\n");
}

// Function to free the polynomial
void freePolynomial(polytype *head)
{
    polytype *current = head;
    while (current != NULL)
    {
        polytype *temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to read polynomial from user
polytype *readPolynomial()
{
    polytype *poly = createNode(0, INT_MAX); // Dummy head for the polynomial
    polytype *tail = poly;                   // Initialize tail
    int terms, coefficient, exponent;

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &terms);

    for (int i = 0; i < terms; i++)
    {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coefficient, &exponent);
        tail = insertTerm(coefficient, exponent, tail); // Use insertTerm
    }

    return poly->next; // Return the actual polynomial, skipping the dummy head
}

// Main program to demonstrate polynomial multiplication
int main()
{
    printf("Enter the first polynomial:\n");
    polytype *poly1 = readPolynomial();

    printf("Enter the second polynomial:\n");
    polytype *poly2 = readPolynomial();

    printf("Polynomial 1: ");
    display(poly1);

    printf("Polynomial 2: ");
    display(poly2);

    polyprod(poly1, poly2);

    // Free memory
    freePolynomial(poly1);
    freePolynomial(poly2);

    return 0;
}
