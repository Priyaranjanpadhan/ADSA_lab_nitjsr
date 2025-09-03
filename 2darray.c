#include <stdio.h>

int main() {
    int rows, cols;
    printf("Enter no. of rows ");
    scanf("%d", &rows);
    printf("Enter no. of columns ");
    scanf("%d", &cols);

    //declaring an integer type 2d array
    int arr[rows][cols];

    // Initialize with 0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = 0;
        }
    }

    //print the 2d array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    //Enter new values for array entry
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter value for position %d,%d: ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }

    // Print updated array
    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}