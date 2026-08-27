#include <TXLib.h>
#include <stdio.h>
#include <string.h>
#include "square_solver.h"

void EscSeq(TextStyle text_style, TextColor text_color, BackgroundColor background_color){ //TODO локальщина некоторая, переделать бы (опционально)
    char esc_sequence[20] = "\x1b[";
    int pos = 2;

    //TODO написать пояснение

    snprintf(esc_sequence + pos++, 2, "%d", text_style);
    if(text_color){
        snprintf(esc_sequence + pos, 4, ";%d", text_color);
        pos += 3;
    }

    if(background_color){
        snprintf(esc_sequence + pos, 4, ";%d", background_color);
        pos += 3;
    }
    snprintf(esc_sequence + pos++, 2, "m");

    printf("%s", esc_sequence);
}

void ResetStyleText(){
    EscSeq(DEFAULT_STYLE_TEXT, DEFAULT_COLOR_TEXT, DEFAULT_COLOR_BACKGROUND);
}
