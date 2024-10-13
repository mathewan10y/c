#include <stdio.h>
#include <stdlib.h>

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
    polytype *temp;
    temp = createNode(coefficient, exponent);
    temp->next = tail->next;
    tail->next = temp;
    return temp;
}

void polyprod(polytype *a, polytype *b)
{
    polytype *result, *tail, *ap, *bp;
    result = tail = createNode(0, INT_MAX);
    {
        for (ap = a; ap != NULL; ap = ap->next)
            for (bp = b; bp != NULL; bp = bp->next)
            {
                tail = result;
                int tcoeff, texp;
                tcoeff = ap->coefficient * bp->coefficient;
                texp = ap->exponent + bp->exponent;
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
    tail = result;
    result = result->next;
    free(tail);
    display(result);
}

// polytype *multiply(polytype *poly1, polytype *poly2)
// {
//     polytype *result = NULL;
//     for (polytype *p1 = poly1; p1 != NULL; p1 = p1->next)
//     {
//         for (polytype *p2 = poly2; p2 != NULL; p2 = p2->next)
//         {
//             int coeff = p1->coefficient * p2->coefficient;
//             int exp = p1->exponent + p2->exponent;
//             result = insertTerm(coeff, exp, result);
//         }
//     }
//     return result;
// }

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
    polytype *poly = NULL;
    int terms, coefficient, exponent;

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &terms);

    for (int i = 0; i < terms; i++)
    {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coefficient, &exponent);
        poly = insertTerm, (coefficient, exponent, poly);
    }

    return poly;
}

// Main program to demonstrate polynomial multiplication
void main()
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
    printf("Result of multiplication: ");

    // Free memory
    freePolynomial(poly1);
    freePolynomial(poly2);
}
