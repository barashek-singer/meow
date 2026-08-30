#ifndef MEOWIO_H_INCLUDED
#define MEOWIO_H_INCLUDED

#include "square_solver.h"

enum ErrCode{
    NO_ERRORS_FOUND         = 0,
    WARNING_SCANF           = (1 << 0),
    WARNING_EXTRA_SYM_AFTER = (1 << 1),
    WARNING_INF_NAN         = (1 << 2),
    ERROR_FOPEN             = (1 << 3),
    ERROR_FCLOSE            = (1 << 4),
    ERROR_FSCANF            = (1 << 5),
    ERROR_CALLOC            = (1 << 6),
    ERROR_FLAG              = (1 << 7)
};
const int MAX_ERROR_BIT = 7;
const int MAX_WARNING_BIT = 2;
const ErrCode WARNING_BITS = (ErrCode)((1 << (MAX_WARNING_BIT + 1)) - 1); //биты, отвечающие за предупреждения
const ErrCode ERRORS_BITS = (ErrCode)(((1 << (MAX_ERROR_BIT + 1)) - 1) - (int)WARNING_BITS); //биты, отвечающие за ошибки

enum TextModification{ //Модификаторы текста
    RESET_TEXT        = 0, //сброс параметров
//---------------------------------------------
    BOLD_TEXT         = 1,
    FAINT_TEXT        = 2,
    ITALIC_TEXT       = 3, //стиль текста
    UNDERLINE_TEXT    = 4,
    SLOW_BLINK_TEXT   = 5,
//---------------------------------------------
    BLACK_TEXT        = 30,
    RED_TEXT          = 31,
    GREEN_TEXT        = 32,
    YELLOW_TEXT       = 33, //цвет текста
    BLUE_TEXT         = 34,
    PURPLE_TEXT       = 35,
    CYAN_TEXT         = 36,
    WHITE_TEXT        = 37,
//---------------------------------------------
    BLACK_BACKGROUND  = 40,
    RED_BACKGROUND    = 41,
    GREEN_BACKGROUND  = 42,
    YELLOW_BACKGROUND = 44, //цвет заднего фона
    BLUE_BACKGROUND   = 44,
    PURPLE_BACKGROUND = 45,
    CYAN_BACKGROUND   = 46,
    WHITE_BACKGROUND  = 47
};

//флаги
#define TEST_FLAG "--tests"
#define HELP_FLAG "--help"

//output
void PrintTextError();
ErrCode UniteErrorCodes(ErrCode error_code1, ErrCode error_code2);
ErrCode IntersectErrorCodes(ErrCode error_code1, ErrCode error_code2);
void PrintFailedTest(size_t num_of_test, const QuadraticEquation quadratic_eq, const QuadraticEquation quadratic_eq_ref);
void PrintRoots(const QuadraticEquation quadratic_eq);
void PrintResult(const QuadraticEquation quadratic_eq);
void PrintAddend(double num, const char* name, int* addends_count);
void PrintSign(double num);
void ShowError(ErrCode error_code);
void ManageErrors(ErrCode error_code);
void PrintHelp();
void ChooseModification(TextModification text_modification);
bool AskQuestion();

//input
void InputCoefficient(double* coefficient, const char letter_coefficient);
void SkipToEndStr();
void SkipBlancSymbols();
ErrCode InputStruct(FILE* fp, QuadraticEquation* quadratic_eq);
void InputCoefficients(QuadraticEquation *quadratic_eq);

#endif
