#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include "math_func.h"
#include "input.h"

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
    while (InputCoefficient(&a, 'a'))
        continue;
    while (InputCoefficient(&b, 'b'))
        continue;
    while (InputCoefficient(&c, 'c'))
        continue;

    int quantity_roots = FindSquareRoots(a, b, c, &first_root, &second_root);
    PrintRoots(a, b, c, quantity_roots, first_root, second_root);

    puts("Mew~");
    return 0;
}

void PrintRoots(double a, double b, double c, int quantity_roots, double first_root, double second_root){
    printf("Уравнение ");
    if(!IsZero(a))
        printf("%lgx^2 + ", a);
    if(!(IsZero(a) && IsZero(b)))
        printf("%lgx + ", b);
    printf("%lg = 0 ", c);

    switch (quantity_roots){
        case ZERO_ROOTS:
                puts("не имеет корней (I've got no roots -^-)");
                break;

        case ONE_ROOT:
                printf("имеет один корень: x = %lg\n", first_root);
                break;

        case TWO_ROOTS:
                printf("имеет два корня: x1 = %lg и x2 = %lg\n", first_root, second_root);
                break;

        case INFINITE_ROOTS:
                puts("имеет бесконечное число решений X^");
                break;

        default:
                puts("Error *.*");
    }
}
