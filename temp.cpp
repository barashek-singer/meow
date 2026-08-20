#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char *end;
    double n = strtod("1234f", &end);
    printf("\"1234f\" --> %lf (%s (%d))\n", n, end, *end == '\0');
    n = strtod("12345", &end);
    printf("\"12345\" --> %lf (%s (%d))\n", n, end, *end == '\0');
    n = strtod("123456 ", &end);
    printf("\"123456 \" --> %lf (%s (%d))\n", n, end, *end == '\0');
}
