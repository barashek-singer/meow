 #include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "square_solver.h"

enum FLAGS{
    NAME_OF_PROGRAM,
    TEST_FLAG = 1,

};

int FindLinearRoots(double k, double c, double* root);
int FindSquareRoots(QuadraticEquation *quadratic_eq);
void PrintFailedTest(int num_of_test, QuadraticEquation quadratic_eq, QuadraticEquation quadratic_eq_ref);
void PrintRoots(QuadraticEquation quadratic_eq);
int StaticSuccessTestsCounter(int num_of_test, QuadraticEquation quadratic_eq_ref);
int RunOneTest(int num_of_test, QuadraticEquation quadratic_eq_ref);
void SwapDouble(double* a, double* b);
double RandDouble();
double RunTests(int rand_tests_count);
bool IsNumber(char* str);

int main(int argc, char* argv[]) {
    /*
    --t - запуск проверки корректности вычисления корней квадратного уравнения
    */
    int flag = 1;
    for (; flag < argc; ++flag){
        if (!strcmp(argv[flag], "--t")){
            int rand_tests_count = 0;

            if (flag + 1 < argc && strncmp(argv[flag + 1], "--", 2)){
                //NOTE 1

                if(argv[++flag][0] == '-'){
                    printf("Количество тестов должно быть неотрицательным");
                    return 0;
                }

                if(!IsNumber(argv[flag])){
                    printf("%s не является числом", argv[flag]);
                    return 0;
                }

                if (strlen(argv[flag]) > 6){
                    printf("Максимальное количество тестов: 999999");
                    return 0;
                }

                rand_tests_count = atoi(argv[flag]);
            }
            printf("\n%.2lf%% всех тестов прошли проверку\n\n", RunTests(rand_tests_count) * 100);
        } else {
            printf("Unknown argument %s", argv[flag]);
            return 0;
        }
    }

    bool continue_program = true;

    while (continue_program){
        QuadraticEquation quadratic_eq;

        puts("Введите коэффициенты квадратного уравнения вида: ax^2 + bx + c = 0");
        while (InputCoefficient(&quadratic_eq.a, 'a') != NO_INPUT_ERROR)
            continue;
        while (InputCoefficient(&quadratic_eq.b, 'b') != NO_INPUT_ERROR)
            continue;
        while (InputCoefficient(&quadratic_eq.c, 'c') != NO_INPUT_ERROR)
            continue;

        quadratic_eq.nroots = FindSquareRoots(&quadratic_eq);
        PrintResult(quadratic_eq);

        continue_program = Question();
    }

    puts("Mew~ (end of program <3)");

    return 0;
}

bool IsNumber(char* str){
    while(*str != '\0')
        if(!isdigit(*str++))
            return false;

    return true;
}

void SwapDouble(double* a, double* b){
    double temp = *a;
    *a = *b;
    *b = temp;
}
void PrintRoots(QuadraticEquation quadratic_eq){
    switch (quadratic_eq.nroots){
        case ZERO_ROOTS:
            puts("0 корней");
            break;

        case ONE_ROOT:
            printf("1 корень: x = %lg\n", quadratic_eq.x1);
            break;

        case TWO_ROOTS:
            printf("2 корня: x1 = %lg и x2 = %lg\n", quadratic_eq.x1, quadratic_eq.x2);
            break;

        case INFINITE_ROOTS:
            puts("Бесконечное число корней");
            break;

        default:
            assert(1 == 0); //специально ложное выражение для ахуевания от того, как сюда попали
    }
}

void PrintFailedTest(int num_of_test, QuadraticEquation quadratic_eq, QuadraticEquation quadratic_eq_ref){
    printf("FAILED на тесте %d\n", num_of_test);

    printf("Коэффициенты: a = %lg, b = %lg, c = %lg\n", quadratic_eq.a, quadratic_eq.b, quadratic_eq.c);

    printf("Ожидалось: ");
    PrintRoots(quadratic_eq_ref);

    printf("Получено: ");
    PrintRoots(quadratic_eq);
}

int RunOneTest(int num_of_test, QuadraticEquation quadratic_eq_ref){
    QuadraticEquation quadratic_eq = {.a = quadratic_eq_ref.a,
                                      .b = quadratic_eq_ref.b,
                                      .c = quadratic_eq_ref.c};

    quadratic_eq.nroots = FindSquareRoots(&quadratic_eq);

    if (quadratic_eq.nroots != quadratic_eq_ref.nroots) {
        PrintFailedTest(num_of_test, quadratic_eq, quadratic_eq_ref);
        return 0;
    }

    switch (quadratic_eq.nroots){
        case ZERO_ROOTS: break;

        case ONE_ROOT:
            if(ComparisonDouble(quadratic_eq.x1, quadratic_eq_ref.x1)){
                PrintFailedTest(num_of_test, quadratic_eq, quadratic_eq_ref);
                return 0;
            }
            break;

        case TWO_ROOTS:
            if(ComparisonDouble(quadratic_eq.x1, quadratic_eq_ref.x1)
            || ComparisonDouble(quadratic_eq.x2, quadratic_eq_ref.x2)){
                PrintFailedTest(num_of_test, quadratic_eq, quadratic_eq_ref);
                return 0;
            }

        case INFINITE_ROOTS:
            break;

        default:
            assert(1 == 0); //специально ложное выражение для ахуевания от того, как сюда попали
    }

    return 1;
}

double RandDouble(){
    return rand() + (double)rand() / RAND_MAX;
}

double RunTests(int rand_tests_count){
    int num_of_test = 0;
    int success_tests_count = 0;

    //NOTE 2

    QuadraticEquation tests_ref[] = {
        {.a = 0,     .b = 0,  .c = 0,  .nroots = INFINITE_ROOTS               },
        {.a = 0,     .b = 0,  .c = 5,  .nroots = ZERO_ROOTS                   },
        {.a = 1,     .b = 1,  .c = 1,  .nroots = ZERO_ROOTS                   },
        {.a = 0,     .b = 1,  .c = 5,  .nroots = ONE_ROOT,  .x1 = -5          },
        {.a = 1,     .b = 0,  .c = 0,  .nroots = ONE_ROOT,  .x1 = 0           },
        {.a = 1,     .b = 0,  .c = -1, .nroots = TWO_ROOTS, .x1 = -1,  .x2 = 1},
        {.a = 2,     .b = -7, .c = 3,  .nroots = TWO_ROOTS, .x1 = 0.5, .x2 = 3},
        {.a = 0.5,   .b = 2,  .c = 0,  .nroots = TWO_ROOTS, .x1 = -4,  .x2 = 0},
        {.a = 1.0/3, .b = -3, .c = 6,  .nroots = TWO_ROOTS, .x1 = 3,   .x2 = 6}
    };

    do {
        success_tests_count += RunOneTest(num_of_test + 1, tests_ref[num_of_test]);
    } while (++num_of_test < (int)(sizeof(tests_ref) / sizeof(QuadraticEquation)));

    for(; rand_tests_count > 0; --rand_tests_count){
        QuadraticEquation quadratic_eq_ref = {.a = RandDouble(), .x1 = RandDouble(), .x2 = RandDouble()};

        if(quadratic_eq_ref.x1 > quadratic_eq_ref.x2)
            SwapDouble(&quadratic_eq_ref.x1, &quadratic_eq_ref.x2);

        quadratic_eq_ref.b = -quadratic_eq_ref.a * (quadratic_eq_ref.x1 + quadratic_eq_ref.x2);
        quadratic_eq_ref.c = quadratic_eq_ref.a * quadratic_eq_ref.x1 * quadratic_eq_ref.x2;
        quadratic_eq_ref.nroots = TWO_ROOTS;

        success_tests_count += RunOneTest(++num_of_test, quadratic_eq_ref);
    }

    return (double)success_tests_count / num_of_test;
}

int FindLinearRoots(double b, double c, double* root){ //bx + c = 0
    assert(root != NULL);

    if (IsZero(b) && IsZero(c)) //Бесконечное число корней
        return INFINITE_ROOTS;

    if (IsZero(b)) //нет корней
        return ZERO_ROOTS;

    //один корень
    *root = -c / b;
    return ONE_ROOT;
}

int FindSquareRoots(QuadraticEquation *quadratic_eq){
    assert(quadratic_eq != NULL);

    if (IsZero(quadratic_eq->a)) //При a = 0 выражение становится линейным
        return FindLinearRoots(quadratic_eq->b, quadratic_eq->c, &(quadratic_eq->x1));

    double D = quadratic_eq->b * quadratic_eq->b - 4 * quadratic_eq->a * quadratic_eq->c; //Дискриминант квадратного уравнения

    if (D < 0) //нет корней
        return ZERO_ROOTS;

    if (IsZero(D)){ //один корень
        quadratic_eq->x1 = -quadratic_eq->b / (2. * quadratic_eq->a);
        return ONE_ROOT;
    }

    //два корня
    quadratic_eq->x1 = (-quadratic_eq->b - sqrt(D)) / (2. * quadratic_eq->a);
    quadratic_eq->x2 = (-quadratic_eq->b + sqrt(D)) / (2. * quadratic_eq->a);
    return TWO_ROOTS;
}

//TODO -
//NOTE 1 - Доработать флаг "-t", который будет принимать аргумент rand_tests_count
//NOTE 2 - Массив структур для плановых тестов
//NOTE 3 - Красивый вывод для ошибок в TODO-1
//NOTE 4 - Делать код читаемым (по возможности сразу)
