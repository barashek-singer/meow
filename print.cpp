#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"

void PrintAddend(double num, const char* name){
    printf("%lg%s", num, name);
}

void PrintSign(double num){
    printf("%s", num < 0 ? " - " : " + ");
}

void PrintResult(QuadraticEquation quadratic_eq){
    printf("”равнение ");
    int addends_count = 0;

    //¬вод первого коэффициента
    if (!IsZero(quadratic_eq.a)){
        PrintAddend(quadratic_eq.a, "x^2");
        ++addends_count;
    }

    //¬вод второго коэффициента
    if (!IsZero(quadratic_eq.b)){
        if (addends_count > 0){ //если лева€ часть имеет хот€ бы одно слагаемое то печатаем + или -, а затем модуль слагаемого
            PrintSign(quadratic_eq.b);
            PrintAddend(fabs(quadratic_eq.b), "x");
        }

        else //если слагаемых в левой части нет - выводи просто число
            PrintAddend(quadratic_eq.b, "x");
        ++addends_count;
    }

    //¬вод третьего коэффициента
    if (!IsZero(quadratic_eq.c)){
        if (addends_count > 0){ //если лева€ часть имеет хот€ бы одно слагаемое то печатаем + или -, а затем модуль слагаемого
            PrintSign(quadratic_eq.c);
            PrintAddend(fabs(quadratic_eq.c), "");
        }

        else //если слагаемых в левой части нет - выводи просто число
            PrintAddend(quadratic_eq.c, "");
        ++addends_count;
    }

    //“ут проверка на то, выводилась ли вообще хоть что-то в левой части уравнени€
    if(addends_count == 0)
        putchar('0');

    //вывод знака равенства и правой части выражени€
    printf(" = 0 ");

    switch (quadratic_eq.nroots){
        case ZERO_ROOTS:
                puts("не имеет корней (I've got no roots -^-)");
                break;

        case ONE_ROOT:
                printf("имеет один корень: x = %lg\n", quadratic_eq.x1);
                break;

        case TWO_ROOTS:
                printf("имеет два корн€: x1 = %lg и x2 = %lg\n", quadratic_eq.x1, quadratic_eq.x2);
                break;

        case INFINITE_ROOTS:
                puts("имеет бесконечное число решений ^_^");
                break;

        default:
                assert(1 == 0); //специально ложное выражение дл€ ахуевани€ от того, как сюда попали
    }
}

bool Question(){
    printf("’отите ли запустить программу снова? (y/N): "); //

    SkipBlancSymbols();

    int answer = getchar(); //isblanc()
    if (answer != 'y')
        return false;

    SkipBlancSymbols();

    if(getchar() != '\n')
        return false;

    return true;
}
