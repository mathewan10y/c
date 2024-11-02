#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Function to convert a dense matrix to tuple form
int convertToTuple(int matrix[MAX_ROWS][MAX_COLS], int tuple[MAX_ROWS * MAX_COLS][3], int rows, int cols)
{
    int t = 0; // Initialize count of non-zero elements to 0
    int n = 1; // Initialize row index for tuple representation to 0
    tuple[0][0] = rows;

    tuple[0][1] = cols;
    // Iterate through the matrix to find non-zero elements
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                // Store the row index, column index, and value in the tuple
                tuple[n][0] = i;            // Row index
                tuple[n][1] = j;            // Column index
                tuple[n][2] = matrix[i][j]; // Value
                n++;                        // Increment tuple index
                t++;                        // Increment count of non-zero elements
            }
        }
    }

    // Store the number of non-zero elements in the first entry of the tuple
    tuple[0][2] = t;

    return t; // Return the count of non-zero elements
}

// Function to print the tuple form of the matrix
void printTuple(int tuple[MAX_ROWS * MAX_COLS][3], int t)
{
    printf("Row\tColumn\tValue\n");
    for (int i = 0; i <= t; i++)
    {
        printf("%d\t%d\t%d\n", tuple[i][0], tuple[i][1], tuple[i][2]);
    }
}

int main()
{
    int matrix[MAX_ROWS][MAX_COLS];
    int rows, cols;
    int tuple[MAX_ROWS * MAX_COLS][3];
    int tran[MAX_ROWS * MAX_COLS][3];
    // To store the tuple representation

    // Input matrix dimensions
    printf("Enter number of rows and columns of the matrix: ");
    scanf("%d %d", &rows, &cols);

    // Input matrix elements
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Convert to tuple form and get the count of non-zero elements
    int t = convertToTuple(matrix, tuple, rows, cols);

    // Print the number of non-zero elements
    printf("Number of non-zero elements: %d\n", t);

    // Print the tuple representation
    printf("Tuple representation of the matrix:\n");
    printTuple(tuple, t); // Pass the actual count of non-zero elements
    trans(tuple, tran);
    printTuple(tran, t);

    return 0;
}

void trans(int sp[][3], int trans[][3])
{

    int i, j, k = 1;
    trans[0][0] = sp[0][1];

    trans[0][1] = sp[0][0];
    trans[0][2] = sp[0][2];
    for (i = 0; i < sp[0][1]; i++)
    {
        for (j = 1; j <= sp[0][2]; j++)
        {
            if (sp[j][1] == i)
            {
                trans[k][0] = sp[j][1];
                trans[k][1] = sp[j][0];
                trans[k][2] = sp[j][2];
                k++;
            }
        }
    }
}