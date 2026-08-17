#include <stdio.h>

int main()
{
    int choice;

    printf("\n----- SIMPLE CALCULATOR -----\n");
    printf("Features available:\n");
    printf("\n1) ADDITION");
    printf("\n2) SUBTRACTION");
    printf("\n3) MULTIPLICATION");
    printf("\n4) DIVISION");
    printf("\n5) MODULUS");
    printf("\n6) EXIT\n");

    do
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                float num1, num2;

                printf("\nEnter the two numbers to add: ");
                scanf("%f %f", &num1, &num2);

                printf("\nResult: %.2f\n", num1 + num2);
                break;
            }

            case 2:
            {
                float num1, num2;

                printf("\nEnter the two numbers to subtract: ");
                scanf("%f %f", &num1, &num2);

                printf("\nResult: %.2f\n", num1 - num2);
                break;
            }

            case 3:
            {
                float num1, num2;

                printf("\nEnter the two numbers to multiply: ");
                scanf("%f %f", &num1, &num2);

                printf("\nResult: %.2f\n", num1 * num2);
                break;
            }

            case 4:
            {
                float num1, num2;

                printf("\nEnter the two numbers to divide: ");
                scanf("%f %f", &num1, &num2);

                if (num2 == 0.0f)
                {
                    printf("\nDivision by zero is not defined.\n");
                }
                else
                {
                    printf("\nResult: %.2f\n", num1 / num2);
                }

                break;
            }

            case 5:
            {
                int num1, num2;

                printf("\nEnter the two integers to find modulus: ");
                scanf("%d %d", &num1, &num2);

                if (num2 == 0)
                {
                    printf("\nModulus by zero is not defined.\n");
                }
                else
                {
                    printf("\nResult: %d\n", num1 % num2);
                }

                break;
            }

            case 6:
            {
                printf("\nThank you for using the calculator.\n");
                break;
            }

            default:
            {
                printf("\nInvalid choice. Please try again.\n");
                break;
            }
        }

    } while (choice != 6);

    return 0;
}
