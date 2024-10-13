#include <stdio.h>

#define MAX_SIZE 100 // Define a maximum size for the array

// Function prototypes for sorting algorithms
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
void printArray(int arr[], int size);

int main()
{
    int n;
    int arr[MAX_SIZE]; // Static array declaration

    // Input array size from the user
    printf("Enter the number of elements in the array (max %d): ", MAX_SIZE);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE)
    {
        printf("Error: Invalid array size.\n");
        return 1;
    }

    // Input array elements from the user
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1. Quick Sort\n");
        printf("2. Merge Sort\n");
        printf("3. Heap Sort\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Create a temporary array to hold the copy of the original array
        int tempArr[MAX_SIZE]; // Static array for the temporary copy

        switch (choice)
        {
        case 1:
        {
            // Quick Sort
            for (int i = 0; i < n; i++)
            {
                tempArr[i] = arr[i]; // Directly copy the elements
            }
            printf("\nOriginal array before Quick Sort: \n");
            printArray(tempArr, n);
            quickSort(tempArr, 0, n - 1);
            printf("Sorted array after Quick Sort: \n");
            printArray(tempArr, n);
            break;
        }
        case 2:
        {
            // Merge Sort
            for (int i = 0; i < n; i++)
            {
                tempArr[i] = arr[i]; // Directly copy the elements
            }
            printf("\nOriginal array befor Merge Sort: \n");
            printArray(tempArr, n);
            mergeSort(tempArr, 0, n - 1);
            printf("Sorted array after Merge Sort: \n");
            printArray(tempArr, n);
            break;
        }
        case 3:
        {
            // Heap Sort
            for (int i = 0; i < n; i++)
            {
                tempArr[i] = arr[i]; // Directly copy the elements
            }
            printf("\nOriginal array before Heap Sort: \n");
            printArray(tempArr, n);
            heapSort(tempArr, n);
            printf("Sorted array after Heap Sort: \n");
            printArray(tempArr, n);
            break;
        }
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Quick Sort implementation
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Merge Sort implementation
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[MAX_SIZE], R[MAX_SIZE]; // Static arrays for merging

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Heap Sort implementation
void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;
        heapify(arr, n, largest);
    }
}

// Utility function to print the array
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
