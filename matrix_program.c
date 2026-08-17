#include <stdio.h>

#define MAX_ROWS 10
#define MAX_COLS 10

void enterMatrix(int matrix[MAX_ROWS][MAX_COLS], int *r, int *c);

void displayMatrix(int matrix[MAX_ROWS][MAX_COLS],
                   int r, int c);

void addMatrix(int matrixA[MAX_ROWS][MAX_COLS],
               int matrixB[MAX_ROWS][MAX_COLS],
               int resultC[MAX_ROWS][MAX_COLS],
               int r, int c);

void multiplyMatrix(int matrixA[MAX_ROWS][MAX_COLS],
                    int matrixB[MAX_ROWS][MAX_COLS],
                    int resultD[MAX_ROWS][MAX_COLS],
                    int r1, int c1, int r2, int c2);

void transposeMatrix(int matrixA[MAX_ROWS][MAX_COLS],
                     int resultT[MAX_ROWS][MAX_COLS],
                     int r1, int c1);

int main()
{
    int choice;

    printf("\n=====================================\n");
    printf(" SIMPLE MATRIX PROGRAM\n");
    printf("=====================================\n");

    do
    {
        int r1, c1, r2, c2;

        int matrixA[MAX_ROWS][MAX_COLS];
        int matrixB[MAX_ROWS][MAX_COLS];

        printf("\n------------- MENU ------------------\n");
        printf("1. Perform Matrix Operations\n");
        printf("2. Exit\n");
        printf("-------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                printf("\nNote: Maximum matrix size is 10 x 10.\n");

                printf("\nEnter Matrix A:\n");
                enterMatrix(matrixA, &r1, &c1);

                printf("\nEnter Matrix B:\n");
                enterMatrix(matrixB, &r2, &c2);

                printf("\nMatrix A:\n");
                displayMatrix(matrixA, r1, c1);

                printf("\nMatrix B:\n");
                displayMatrix(matrixB, r2, c2);

                /* Matrix Addition */
                if (r1 != r2 || c1 != c2)
                {
                    printf("\nMatrix addition is not possible.\n");
                    printf("Both matrices must have the same dimensions.\n");
                }
                else
                {
                    int resultC[MAX_ROWS][MAX_COLS];

                    addMatrix(matrixA, matrixB,
                              resultC, r1, c1);

                    printf("\nMatrix A + Matrix B:\n");
                    displayMatrix(resultC, r1, c1);
                }

                /* Matrix Multiplication */
                if (c1 != r2)
                {
                    printf("\nMatrix multiplication is not possible.\n");
                    printf("Columns of Matrix A must equal ");
                    printf("rows of Matrix B.\n");
                }
                else
                {
                    int resultD[MAX_ROWS][MAX_COLS];

                    multiplyMatrix(matrixA, matrixB,
                                   resultD,
                                   r1, c1, r2, c2);

                    printf("\nMatrix A x Matrix B:\n");
                    displayMatrix(resultD, r1, c2);
                }

                /* Transpose of Matrix A */
                {
                    int resultTA[MAX_ROWS][MAX_COLS];

                    transposeMatrix(matrixA,
                                    resultTA,
                                    r1, c1);

                    printf("\nTranspose of Matrix A:\n");
                    displayMatrix(resultTA, c1, r1);
                }

                /* Transpose of Matrix B */
                {
                    int resultTB[MAX_ROWS][MAX_COLS];

                    transposeMatrix(matrixB,
                                    resultTB,
                                    r2, c2);

                    printf("\nTranspose of Matrix B:\n");
                    displayMatrix(resultTB, c2, r2);
                }

                break;
            }

            case 2:
            {
                printf("\nThank you for using the Matrix Program!\n");
                break;
            }

            default:
            {
                printf("\nInvalid choice! Please select 1 or 2.\n");
                break;
            }
        }

    } while (choice != 2);

    return 0;
}


/* =====================================
   ENTER MATRIX
   ===================================== */
void enterMatrix(int matrix[MAX_ROWS][MAX_COLS],
                 int *r, int *c)
{
    do
    {
        printf("\nEnter number of rows (1-10): ");
        scanf("%d", r);

        if (*r < 1 || *r > 10)
        {
            printf("Rows must be between 1 and 10.\n");
        }

    } while (*r < 1 || *r > 10);


    do
    {
        printf("Enter number of columns (1-10): ");
        scanf("%d", c);

        if (*c < 1 || *c > 10)
        {
            printf("Columns must be between 1 and 10.\n");
        }

    } while (*c < 1 || *c > 10);


    for (int i = 0; i < *r; i++)
    {
        for (int j = 0; j < *c; j++)
        {
            printf("Enter matrix[%d][%d]: ",
                   i + 1, j + 1);

            scanf("%d", &matrix[i][j]);
        }
    }
}


/* =====================================
   DISPLAY MATRIX
   ===================================== */
void displayMatrix(int matrix[MAX_ROWS][MAX_COLS],
                   int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d\t", matrix[i][j]);
        }

        printf("\n");
    }
}


/* =====================================
   MATRIX ADDITION
   ===================================== */
void addMatrix(int matrixA[MAX_ROWS][MAX_COLS],
               int matrixB[MAX_ROWS][MAX_COLS],
               int resultC[MAX_ROWS][MAX_COLS],
               int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            resultC[i][j] =
                matrixA[i][j] + matrixB[i][j];
        }
    }
}


/* =====================================
   MATRIX MULTIPLICATION
   ===================================== */
void multiplyMatrix(int matrixA[MAX_ROWS][MAX_COLS],
                    int matrixB[MAX_ROWS][MAX_COLS],
                    int resultD[MAX_ROWS][MAX_COLS],
                    int r1, int c1,
                    int r2, int c2)
{
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            resultD[i][j] = 0;

            for (int k = 0; k < c1; k++)
            {
                resultD[i][j] +=
                    matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}


/* =====================================
   MATRIX TRANSPOSE
   ===================================== */
void transposeMatrix(int matrixA[MAX_ROWS][MAX_COLS],
                     int resultT[MAX_ROWS][MAX_COLS],
                     int r1, int c1)
{
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++)
        {
            resultT[j][i] = matrixA[i][j];
        }
    }
}


