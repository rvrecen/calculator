#include <stdio.h>

// Function prototypes
void get_input(char *operator, double *num1, double *num2);
double calculate(char operator, double num1, double num2, int *error);
void display_result(double result);
void display_error(int error_code);

int main() {
    char operator;
    double num1, num2, result;
    int error = 0;

    get_input(&operator, &num1, &num2);
    result = calculate(operator, num1, num2, &error);

    if (error) {
        display_error(error);
    } else {
        display_result(result);
    }

    return 0;
}

void get_input(char *operator, double *num1, double *num2) {
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", operator);

    printf("Enter two numbers: ");
    scanf("%lf %lf", num1, num2);
}

double calculate(char operator, double num1, double num2, int *error) {
    switch(operator) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 != 0) {
                return num1 / num2;
            } else {
                *error = 1;
                return 0;
            }
        default:
            *error = 2;
            return 0;
    }
}

void display_result(double result) {
    printf("Result: %.2f\n", result);
}

void display_error(int error_code) {
    switch(error_code) {
        case 1:
            printf("Error: Division by zero\n");
            break;
        case 2:
            printf("Error: Invalid operator\n");
            break;
        default:
            printf("Unknown error occurred\n");
    }
}
