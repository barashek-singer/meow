#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int InputCoefficient(double* coefficient, char letter_coefficient){

    printf("¬ведите %c: ", letter_coefficient);

    char ch;

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
