#include <stdio.h>

#define MAX_TERMS 100

// Structure for storing polynomial terms
struct Poly
{
    int coeff;
    int expo;
};

// Array to store polynomial terms
struct Poly term[MAX_TERMS];
int free = 0; // Keeps track of the next available position in term array

// Function to create a new term
void newterm(int coeff, int expo)
{
    term[free].coeff = coeff;
    term[free].expo = expo;
    free++;
}

// Function to add two polynomials
int polyadd(int af, int al, int bf, int bl, int cf)
{
    free = cf; // Reset free to the starting index for the result polynomial

    // Set temporary variables
    int p = af; // Start index of polynomial A
    int q = bf; // Start index of polynomial B

    while (p <= al && q <= bl)
    {
        if (term[p].expo > term[q].expo)
        {
            newterm(term[p].coeff, term[p].expo);
            p++;
        }
        else if (term[p].expo < term[q].expo)
        {
            newterm(term[q].coeff, term[q].expo);
            q++;
        }
        else
        {
            // If the exponents are the same, add the coefficients
            int sum = term[p].coeff + term[q].coeff;
            if (sum != 0)
            { // Only add if the sum is not zero
                newterm(sum, term[p].expo);
            }
            p++;
            q++;
        }
    }

    // Add remaining terms of polynomial A
    while (p <= al)
    {
        newterm(term[p].coeff, term[p].expo);
        p++;
    }

    // Add remaining terms of polynomial B
    while (q <= bl)
    {
        newterm(term[q].coeff, term[q].expo);
        q++;
    }

    return free - 1; // Return the end index of the result polynomial
}

// Function to print a polynomial
void printPoly(int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        printf("%dx^%d", term[i].coeff, term[i].expo);
        if (i < end)
        {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to input a polynomial from the user
void inputPoly(int *start, int *end)
{
    int n;
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);

    *start = free;

    for (int i = 0; i < n; i++)
    {
        int coeff, expo;
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &expo);
        newterm(coeff, expo);
    }

    *end = free - 1;
}

int main()
{
    int af, al, bf, bl, cf, cl;

    // Input polynomial A
    printf("Input Polynomial A:\n");
    inputPoly(&af, &al);

    // Input polynomial B
    printf("Input Polynomial B:\n");
    inputPoly(&bf, &bl);

    printf("Polynomial A: ");
    printPoly(af, al);

    printf("Polynomial B: ");
    printPoly(bf, bl);

    // Perform polynomial addition with cf as the starting index for result terms
    cf = free;                        // Capture current free position as start of result polynomial
    cl = polyadd(af, al, bf, bl, cf); // `cl` now holds the end index returned by `polyadd`

    printf("Resultant Polynomial after Addition: ");
    printPoly(cf, cl);

    return 0;
}
