#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"
#include "print.h"

void ShowError(ErrCode error_code){
    switch (error_code){
        case ERROR_SCANF:
            puts("Ну, число как минимум должно начинаться с цифры или его знака (не более одного)");
            break;

        case ERROR_EXTRA_SYMBOLS_AFTER:
            puts("После числа не должно быть символов за исключением пробельных");
            break;

        case ERROR_INF_NAN:
            puts("Не, ну ты издеваешься");
            break;

        case ERROR_FOPEN:
            puts("Некорректное открытие файла");
            exit(1);

        case ERROR_FCLOSE:
            puts("Некорректное закрытие файла");
            exit(1);

        case ERROR_FSCANF:
            puts("Некорректное считывание с файла");
            exit(1);

        case ERROR_CALLOC:
            puts("Что-то с динамической памятью, короче пака");
            exit(1);

        case NO_ERRORS_FOUND:
            break;

        default:
            assert(false);
    }
}

void PrintAddend(double num, const char* name){
    assert(name != NULL);
    printf("%lg%s", num, name);
}

void PrintSign(double num){
    printf(" %c ", (num < 0) ? '-' : '+');
}

void PrintResult(const QuadraticEquation quadratic_eq){
    printf("Уравнение ");
    int addends_count = 0;

    //Ввод первого коэффициента
    if (!IsZero(quadratic_eq.a)){
        PrintAddend(quadratic_eq.a, "x^2");
        ++addends_count;
    }

    //Ввод второго коэффициента
    if (!IsZero(quadratic_eq.b)){
        if (addends_count > 0){ //если левая часть имеет хотя бы одно слагаемое то печатаем + или -, а затем модуль слагаемого
            PrintSign(quadratic_eq.b);
            PrintAddend(fabs(quadratic_eq.b), "x");
        }

        else //если слагаемых в левой части нет - выводи просто число
            PrintAddend(quadratic_eq.b, "x");
        ++addends_count;
    }

    //Ввод третьего коэффициента
    if (!IsZero(quadratic_eq.c)){
        if (addends_count > 0){ //если левая часть имеет хотя бы одно слагаемое то печатаем + или -, а затем модуль слагаемого
            PrintSign(quadratic_eq.c);
            PrintAddend(fabs(quadratic_eq.c), "");
        }

        else //если слагаемых в левой части нет - выводи просто число
            PrintAddend(quadratic_eq.c, "");
        ++addends_count;
    }

    //Тут проверка на то, выводилась ли вообще хоть что-то в левой части уравнения
    if(addends_count == 0)
        putchar('0');

    //вывод знака равенства и правой части выражения
    printf(" = 0 ");

    PrintRoots(quadratic_eq);
}

bool AskQuestion(){
    printf("Хотите ли запустить программу снова? (y/N): "); //???????????????????????????????????????????????????????????????????????????????

    SkipBlancSymbols();

    int answer = getchar();
    if (answer != 'y')
        return false;

    SkipBlancSymbols();

    if(getchar() != '\n')
        return false;

    return true;
}

void PrintHelp(){
    putchar('\n');
    puts("Данная программа по введённым коэффициентам квадратного трёхчлена решает квадратное уравнение");
    putchar('\n');
    puts("Доступные флаги:");
    putchar('\n');
    printf("%s rand_tests_count - запуск проверки корректности вычисления корней квадратного уравнения, "
        "rand_tests_count из которых - рандомные (по умолчанию 0)", TEST_FLAG);
    printf("%s - Сводка флагов и что вообще делает программа (действительно)", HELP_FLAG);
    putchar('\n');
}

void PrintRoots(const QuadraticEquation quadratic_eq){ /////////
    switch (quadratic_eq.nroots){
        case ZERO_ROOTS:
            puts("имеет 0 корней");
            break;

        case ONE_ROOT:
            printf("имеет 1 корень: x = %lg\n", quadratic_eq.x1);
            break;

        case TWO_ROOTS:
            printf("имеет 2 корня: x1 = %lg и x2 = %lg\n", quadratic_eq.x1, quadratic_eq.x2);
            break;

        case INFINITE_ROOTS:
            puts("имеет бесконечное число корней");
            break;

        default:
            assert(2 + 2 == 5); //специально ложное выражение для ахуевания от того, как сюда попали
    }
}

void PrintFailedTest(size_t num_of_test, const QuadraticEquation quadratic_eq, const QuadraticEquation quadratic_eq_ref){ //color
    printf("FAILED на тесте %zu\n", num_of_test);

    printf("Коэффициенты: a = %lg, b = %lg, c = %lg\n", quadratic_eq.a, quadratic_eq.b, quadratic_eq.c);

    printf("Ожидалось: ");
    PrintRoots(quadratic_eq_ref);

    printf("Получено: ");
    PrintRoots(quadratic_eq);
}
