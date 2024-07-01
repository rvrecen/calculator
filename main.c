#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Function prototypes
void display_menu();
void get_input(int *choice, double *num1, double *num2);
double calculate(int choice, double num1, double num2, int *error);
void display_result(double result);
void display_error(int error_code);

int main() {
    int choice, error = 0;
    double num1, num2, result;

    while (1) {
        display_menu();
        get_input(&choice, &num1, &num2);
        
        if (choice == 0) {
            printf("Exiting the calculator. Goodbye!\n");
            break;
        }

        result = calculate(choice, num1, num2, &error);

        if (error) {
            display_error(error);
        } else {
            display_result(result);
        }
    }

    return 0;
}

void display_menu() {
    printf("\nScientific Calculator\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Square root\n");
    printf("6. Power\n");
    printf("7. Sine\n");
    printf("8. Cosine\n");
    printf("9. Tangent\n");
    printf("10. Natural logarithm\n");
    printf("0. Exit\n");
}

void get_input(int *choice, double *num1, double *num2) {
    printf("Enter your choice (0-10): ");
    scanf("%d", choice);

    if (*choice >= 1 && *choice <= 4) {
        printf("Enter two numbers: ");
        scanf("%lf %lf", num1, num2);
    } else if (*choice >= 5 && *choice <= 10) {
        printf("Enter a number: ");
        scanf("%lf", num1);
    }
}

double calculate(int choice, double num1, double num2, int *error) {
    switch(choice) {
        case 1: return num1 + num2;
        case 2: return num1 - num2;
        case 3: return num1 * num2;
        case 4:
            if (num2 != 0) {
                return num1 / num2;
            } else {
                *error = 1;
                return 0;
            }
        case 5:
            if (num1 >= 0) {
                return sqrt(num1);
            } else {
                *error = 2;
                return 0;
            }
        case 6: return pow(num1, num2);
        case 7: return sin(num1);
        case 8: return cos(num1);
        case 9: return tan(num1);
        case 10:
            if (num1 > 0) {
                return log(num1);
            } else {
                *error = 3;
                return 0;
            }
        default:
            *error = 4;
            return 0;
    }
}

void display_result(double result) {
    printf("Result: %f\n", result);
}

void display_error(int error_code) {
    switch(error_code) {
        case 1:
            printf("Error: Division by zero\n");
            break;
        case 2:
            printf("Error: Cannot calculate square root of a negative number\n");
            break;
        case 3:
            printf("Error: Cannot calculate logarithm of a non-positive number\n");
            break;
        case 4:
            printf("Error: Invalid choice\n");
            break;
        default:
            printf("Unknown error occurred\n");
    }
}