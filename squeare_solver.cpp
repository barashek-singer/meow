#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include "math_func.h"
#include "input.h"

void PrintRoots(double a, double b, double c, int quantity_roots, double first_root, double second_root);
void PrintAddend(double a, short first_addend);

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

void PrintAddend(double a, short first_addend){
    putchar(' ');
    if(first_addend){
        if(ComparisonDouble(a, 1))
            return;
        printf("%lg", a);
        return;
    }
    putchar(a < 0 ? '-' : '+');
    putchar(' ');
    if(!ComparisonDouble(a, 1))
        printf("%lg", fabs(a));
}

void PrintRoots(double a, double b, double c, int quantity_roots, double first_root, double second_root){
    printf("Уравнение");

    short first_addend = true;

    if(!IsZero(a)){
        PrintAddend(a, first_addend); //1x^2 + -0x + -0 = 0 <=> x^2 = 0
        printf("x^2");
        first_addend = false;
    }

    if(!IsZero(b)){
        PrintAddend(b, first_addend);
        printf("x");
        first_addend = false;
    }

    if(!IsZero(c)){
        PrintAddend(c, first_addend);
        if(ComparisonDouble(c, 1))
            putchar('1');
        first_addend = false;
    }

    if(first_addend)
        printf(" 0");

    printf(" = 0 ");

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
