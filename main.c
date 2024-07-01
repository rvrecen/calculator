#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <string.h>

#define PI 3.14159265358979323846

typedef struct {
    double real;
    double imag;
} Complex;

// Function prototypes
void display_menu();
void get_input(int *choice, double *num1, double *num2, Complex *c1, Complex *c2);
void calculate(int choice, double num1, double num2, Complex c1, Complex c2);
void display_result(double result);
void display_complex_result(Complex result);
void display_error(int error_code);

// Engineering-specific function prototypes
double celsius_to_fahrenheit(double celsius);
double fahrenheit_to_celsius(double fahrenheit);
double ohms_law(double v, double i, double r, char solve_for);
double parallel_resistance(double r1, double r2);

int main() {
    int choice;
    double num1, num2;
    Complex c1, c2;

    while (1) {
        display_menu();
        get_input(&choice, &num1, &num2, &c1, &c2);
        
        if (choice == 0) {
            printf("Exiting the calculator. Goodbye!\n");
            break;
        }

        calculate(choice, num1, num2, c1, c2);
    }

    return 0;
}

void display_menu() {
    printf("\nEngineering Calculator\n");
    printf("1. Basic Operations (+, -, *, /)\n");
    printf("2. Power and Root\n");
    printf("3. Trigonometric Functions\n");
    printf("4. Logarithmic Functions\n");
    printf("5. Complex Number Operations\n");
    printf("6. Temperature Conversion\n");
    printf("7. Ohm's Law\n");
    printf("8. Parallel Resistance\n");
    printf("0. Exit\n");
}

void get_input(int *choice, double *num1, double *num2, Complex *c1, Complex *c2) {
    printf("Enter your choice: ");
    scanf("%d", choice);

    switch(*choice) {
        case 1:
        case 2:
            printf("Enter two numbers: ");
            scanf("%lf %lf", num1, num2);
            break;
        case 3:
        case 4:
            printf("Enter a number: ");
            scanf("%lf", num1);
            break;
        case 5:
            printf("Enter first complex number (real imag): ");
            scanf("%lf %lf", &c1->real, &c1->imag);
            printf("Enter second complex number (real imag): ");
            scanf("%lf %lf", &c2->real, &c2->imag);
            break;
        case 6:
        case 7:
        case 8:
            // Input will be handled in the specific functions
            break;
    }
}

void calculate(int choice, double num1, double num2, Complex c1, Complex c2) {
    double result;
    Complex complex_result;
    char operation;

    switch(choice) {
        case 1:
            printf("Enter operation (+, -, *, /): ");
            scanf(" %c", &operation);
            switch(operation) {
                case '+': result = num1 + num2; break;
                case '-': result = num1 - num2; break;
                case '*': result = num1 * num2; break;
                case '/': 
                    if (num2 != 0) result = num1 / num2;
                    else { display_error(1); return; }
                    break;
                default: display_error(4); return;
            }
            display_result(result);
            break;
        case 2:
            printf("Enter operation (p for power, r for root): ");
            scanf(" %c", &operation);
            if (operation == 'p') result = pow(num1, num2);
            else if (operation == 'r') {
                if (num1 >= 0) result = pow(num1, 1/num2);
                else { display_error(2); return; }
            }
            else { display_error(4); return; }
            display_result(result);
            break;
        case 3:
            printf("Enter function (s for sin, c for cos, t for tan): ");
            scanf(" %c", &operation);
            switch(operation) {
                case 's': result = sin(num1); break;
                case 'c': result = cos(num1); break;
                case 't': result = tan(num1); break;
                default: display_error(4); return;
            }
            display_result(result);
            break;
        case 4:
            printf("Enter function (n for natural log, l for log10): ");
            scanf(" %c", &operation);
            if (num1 <= 0) { display_error(3); return; }
            if (operation == 'n') result = log(num1);
            else if (operation == 'l') result = log10(num1);
            else { display_error(4); return; }
            display_result(result);
            break;
        case 5:
            printf("Enter operation (+, -, *, /): ");
            scanf(" %c", &operation);
            switch(operation) {
                case '+':
                    complex_result.real = c1.real + c2.real;
                    complex_result.imag = c1.imag + c2.imag;
                    break;
                case '-':
                    complex_result.real = c1.real - c2.real;
                    complex_result.imag = c1.imag - c2.imag;
                    break;
                case '*':
                    complex_result.real = c1.real * c2.real - c1.imag * c2.imag;
                    complex_result.imag = c1.real * c2.imag + c1.imag * c2.real;
                    break;
                case '/':
                    if (c2.real == 0 && c2.imag == 0) { display_error(1); return; }
                    double denom = c2.real * c2.real + c2.imag * c2.imag;
                    complex_result.real = (c1.real * c2.real + c1.imag * c2.imag) / denom;
                    complex_result.imag = (c1.imag * c2.real - c1.real * c2.imag) / denom;
                    break;
                default: display_error(4); return;
            }
            display_complex_result(complex_result);
            break;
        case 6:
            printf("Enter conversion (c for C to F, f for F to C): ");
            scanf(" %c", &operation);
            printf("Enter temperature: ");
            scanf("%lf", &num1);
            if (operation == 'c') result = celsius_to_fahrenheit(num1);
            else if (operation == 'f') result = fahrenheit_to_celsius(num1);
            else { display_error(4); return; }
            display_result(result);
            break;
        case 7:
            printf("Enter known values (format: V=120 I=2 R=60): ");
            char input[20];
            scanf("%s %s %s", input, input + 7, input + 14);
            double v = 0, i = 0, r = 0;
            char solve_for = '\0';
            if (input[0] == 'V') sscanf(input + 2, "%lf", &v);
            else solve_for = 'V';
            if (input[7] == 'I') sscanf(input + 9, "%lf", &i);
            else solve_for = 'I';
            if (input[14] == 'R') sscanf(input + 16, "%lf", &r);
            else solve_for = 'R';
            result = ohms_law(v, i, r, solve_for);
            printf("%c = %f\n", solve_for, result);
            break;
        case 8:
            printf("Enter two resistance values: ");
            scanf("%lf %lf", &num1, &num2);
            result = parallel_resistance(num1, num2);
            display_result(result);
            break;
        default:
            display_error(4);
            return;
    }
}

void display_result(double result) {
    printf("Result: %f\n", result);
}

void display_complex_result(Complex result) {
    printf("Result: %f + %fi\n", result.real, result.imag);
}

void display_error(int error_code) {
    switch(error_code) {
        case 1: printf("Error: Division by zero\n"); break;
        case 2: printf("Error: Cannot calculate root of a negative number\n"); break;
        case 3: printf("Error: Cannot calculate logarithm of a non-positive number\n"); break;
        case 4: printf("Error: Invalid input\n"); break;
        default: printf("Unknown error occurred\n");
    }
}

double celsius_to_fahrenheit(double celsius) {
    return (celsius * 9/5) + 32;
}

double fahrenheit_to_celsius(double fahrenheit) {
    return (fahrenheit - 32) * 5/9;
}

double ohms_law(double v, double i, double r, char solve_for) {
    switch(solve_for) {
        case 'V': return i * r;
        case 'I': return v / r;
        case 'R': return v / i;
        default: return 0;
    }
}

double parallel_resistance(double r1, double r2) {
    return (r1 * r2) / (r1 + r2);
}