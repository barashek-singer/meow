#ifndef SQUARE_SOLVER_H_INCLUDED
#define SQUARE_SOLVER_H_INCLUDED

#include <stdio.h>

const double EPS = 1e-3;

enum LessMore{
    LESS  = -1,
    EQUAL = 0,
    MORE  = 1
};

enum ErrCode{
    NO_ERRORS_FOUND           = 0,
    ERROR_SCANF               = 1,
    ERROR_EXTRA_SYMBOLS_AFTER = 2,
    ERROR_INF_NAN             = 3,
    ERROR_FOPEN               = 4,
    ERROR_FCLOSE              = 5,
    ERROR_FSCANF              = 6,
    ERROR_CALLOC              = 7
};

enum RootsCount{
    ZERO_ROOTS     = 0,
    ONE_ROOT       = 1,
    TWO_ROOTS      = 2,
    INFINITE_ROOTS = 3
};

enum TextStyle{
    DEFAULT_STYLE_TEXT = 0,
    BOLD_TEXT = 1,
    FAINT_TEXT = 2,
    ITALIC_TEXT = 3,
    UNDERLINE_TEXT = 4,
    SLOW_BLINK_TEXT = 5
};

enum TextColor{
    DEFAULT_COLOR_TEXT = 0,
    BLACK_TEXT = 30,
    RED_TEXT = 31,
    GREEN_TEXT = 32,
    YELLOW_TEXT = 33,
    BLUE_TEXT = 34,
    MAGENTA_TEXT = 35,
    CYAN_TEXT = 36,
    WHITE_TEXT = 37
};

enum BackgroundColor{
    DEFAULT_COLOR_BACKGROUND = 0,
    BLACK_BACKGROUND = 40,
    RED_BACKGROUND = 41,
    GREEN_BACKGROUND = 42,
    YELLOW_BACKGROUND = 44,
    BLUE_BACKGROUND = 44,
    MAGENTA_BACKGROUND = 45,
    CYAN_BACKGROUND = 46,
    WHITE_BACKGROUND = 47
};

struct QuadraticEquation{ //ax^2 + bx + c = a(x - x1)(x - x2)
    double a, b, c;
    RootsCount nroots;
    double x1, x2;
};

void SwapDouble(double* a, double* b);
double RandDouble();
ErrCode RunTests(int rand_tests_count);
int RunOneTest(size_t num_of_test, const QuadraticEquation quadratic_eq_ref); //можно добавить enum StatusTest
void EscSeq(TextStyle text_style, TextColor text_color, BackgroundColor background_color);
void ResetStyleText();
ErrCode InputStruct(FILE* fp, QuadraticEquation* quadratic_eq);
void InputCoefficients(QuadraticEquation *quadratic_eq);
LessMore CmpDouble(double a, double b);
bool IsZero(double a);
void ShowError(ErrCode error_code);
ErrCode InputCoefficient(double* coefficient, const char letter_coefficient);
void SkipToEndStr(); //EOF
void SkipBlancSymbols(); //EOF
RootsCount FindLinearRoots(double k, double c, double* root);
RootsCount FindSquareRoots(QuadraticEquation *quadratic_eq);

#endif
