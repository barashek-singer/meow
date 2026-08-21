#include "TXLib.h"
#include <stdio.h>
#include "print_roots.h"

//TODO - костанты кейсов


const int INFINITE_ROOTS = 10000000;

void PrintRoots(int quantity_roots, double first_root, double second_root){
    switch (quantity_roots){
        case 0:
                puts("I've got no roots -^-");
                break;
        case 1:
                printf("Уравнение имеет один корень: %lg\n", first_root);
                break;
        case 2:
                printf("Уравнения имеет два корня: %lg and %lg\n", first_root, second_root);
                break;
        case INFINITE_ROOTS:
                puts("Уравнение имеет бесконечное число решений X^");
                break;
        default:
                puts("Error *.*");
    }
}
