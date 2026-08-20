#include <stdio.h>
#include <math.h>
#include "solve_square.h"
#include "print_roots.h"
#include "input_coefficient.h"

int main(void) {
    double a = NAN, b = NAN, c = NAN, first_root = NAN, second_root = NAN;

    puts("Введите коэффициенты квадратного уравнения");

    while (!InputCoefficient(&a, 'a'))
        puts("Не, введи одно число, например: 2, 5e-3 или 12.59");

    while (!InputCoefficient(&b, 'b'))
        puts("Не, введи одно число, например: 2, 5e-3 или 12.59");

    while (!InputCoefficient(&c, 'c'))
        puts("Не, введи одно число, например: 2, 5e-3 или 12.59");

    int quantity_roots = FindSquareRoots(a, b, c, &first_root, &second_root);
    PrintRoots(quantity_roots, first_root, second_root);

    return 0;
}
