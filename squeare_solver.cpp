#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include "math_func.h"

int InputCoefficient(double* coefficient, char letter_coefficient);
void PrintRoots(double a, double b, double c, int quantity_roots, double first_root, double second_root);

enum QuantityRoots
{
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};

int main(void) {
    double a = NAN, b = NAN, c = NAN, first_root = NAN, second_root = NAN;

    puts("Введите коэффициенты квадратного уравнения вида: ax^2 + bx + c = 0");
    while (!InputCoefficient(&a, 'a'))
        puts("Не, введи одно число, например: 2, 5e-3 или 12.59");
    while (!InputCoefficient(&b, 'b'))
        puts("Не, введи одно число, например: 2, 5e-3 или 12.59");
    while (!InputCoefficient(&c, 'c'))
        puts("Не, введи одно число, например: 2, 5e-3 или 12.59");

    int quantity_roots = FindSquareRoots(a, b, c, &first_root, &second_root);
    PrintRoots(a, b, c, quantity_roots, first_root, second_root);

    return 0;
}

int InputCoefficient(double* coefficient, char letter_coefficient){

    printf("Введите %c: ", letter_coefficient);

    int ch = '\0';

    scanf("%lf", coefficient);
    while((ch = getchar()) != '\n')
        if(!isspace(ch)){
            scanf("%*[^\n]");
            return 0;
        }
    if(ch != '\n')
        scanf("%*[^\n]");

    return isfinite(*coefficient);
}

void PrintRoots(double a, double b, double c, int quantity_roots, double first_root, double second_root){
    switch (quantity_roots){
        case ZERO_ROOTS:
                if(IsZero(a) && IsZero(b))
                    printf("Уравнение %lg = 0 не имеет корней", c);
                else
                    printf("Уравнение %lgx^2 + %lgx + %lg = 0 не имеет корней (I've got no roots -^-)", a, b, c);
                break;

        case ONE_ROOT:
                if (IsZero(a))
                    printf("Уравнение %lgx + %lg = 0 имеет один корень: x = %lg", b, c, first_root);
                else
                    printf("Уравнение %lgx^2 + %lgx + %lg = 0 имеет один корень: x = %lg\n", a, b, c, first_root);
                break;

        case TWO_ROOTS:
                printf("Уравнения %lgx^2 + %lgx + %lg = 0 имеет два корня: "
                        "x1 = %lg и x2 = %lg\n", a, b, c, first_root, second_root);
                break;

        case INFINITE_ROOTS:
                puts("Уравнение 0 = 0 имеет бесконечное число решений X^");
                break;

        default:
                puts("Error *.*");
    }
}
