#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include "square_solver.h"

void PrintAddend(double num, const char* name){
    printf("%lg%s", num, name);
}

void PrintSign(double num){
    printf("%s", num < 0 ? " - " : " + ");
}

void PrintRoots(QuadraticEquation quadratic_equation, int roots_count){
    printf("”равнение ");
    int addends_count = 0;

    //¬вод первого коэффициента
    if(!IsZero(quadratic_equation.a)){
        PrintAddend(quadratic_equation.a, "x^2");
        ++addends_count;
    }

    //¬вод второго коэффициента
    if(!IsZero(quadratic_equation.b)){
        if(addends_count > 0){ //если лева€ часть имеет хот€ бы одно слагаемое то печатаем + или -, а затем модуль слагаемого
            PrintSign(quadratic_equation.b);
            PrintAddend(fabs(quadratic_equation.b), "x");
        }

        else //если слагаемых в левой части нет - выводи просто число
            PrintAddend(quadratic_equation.b, "x");
        ++addends_count;
    }

    //¬вод третьего коэффициента
    if(!IsZero(quadratic_equation.c)){
        if(addends_count > 0){ //если лева€ часть имеет хот€ бы одно слагаемое то печатаем + или -, а затем модуль слагаемого
            PrintSign(quadratic_equation.c);
            PrintAddend(fabs(quadratic_equation.c), "");
        }

        else //если слагаемых в левой части нет - выводи просто число
            PrintAddend(quadratic_equation.c, "");
        ++addends_count;
    }

    //“ут проверка на то, выводилась ли вообще хоть что-то в левой части уравнени€
    if(addends_count == 0)
        putchar('0');

    //вывод знака равенства и правой части выражени€
    printf(" = 0 ");

    switch (roots_count){
        case ZERO_ROOTS:
                puts("не имеет корней (I've got no roots -^-)");
                break;

        case ONE_ROOT:
                printf("имеет один корень: x = %lg\n", quadratic_equation.first_root);
                break;

        case TWO_ROOTS:
                printf("имеет два корн€: x1 = %lg и x2 = %lg\n", quadratic_equation.first_root, quadratic_equation.second_root);
                break;

        case INFINITE_ROOTS:
                puts("имеет бесконечное число решений ^_^");
                break;

        default:
                puts("Error *.*");
    }
}
