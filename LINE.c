/*
 * LINE.c
 *
 *  Created on: 25 Jan 2021
 *      Author: helios
 */
// 1. Preprocessor Directives Section
#include <string.h>
#include <LINE.h>

// 2. Variable Declaration Section
int inPos = 0;
int validNum;
int validOp;
char CALC_line[16] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
size_t lineSize = sizeof(CALC_line);


// 3. Subroutines Section
void LINE_counter(void){ // called overtime a value is printed to the LCD
    inPos++;
}

void LINE_counterReset(void){
    inPos = 0;
}

void LINE_track(char c){
    CALC_line[inPos] = c;
}

void LINE_trackReset(void){
    for(int n = 0; n <= 15; n++){
        CALC_line[n] = '0';
    }
}

void LINE_Reset(void){
    LINE_counterReset();
    LINE_trackReset();
}

// Brackets Indices Division Multiplication Addition Subtraction
int LINE_validate_num(void) {
    for (int i = 0; i < lineSize; i++) {
        char current = CALC_line[i];
        //if ( !isdigit(current) && // check for numbers using isdigit(int i) from ctype.h library
        if (!(current >= '0' && current <= '9') && // implementation without using ctype.h
                current != 'E' && // source: https://stackoverflow.com/questions/8611815/determine-if-char-is-a-num-or-letter
                current != 'x' && // chars are integers and so can actually just be compared
                current != '/' &&
                current != '+' &&
                current != '-' &&
                current != '.' ) {
            return 0;
        }
        else {
            return 1;
        }
    }
}

int LINE_validate_firstOp(void){
    // if first character is an operator, return invalid expr. (syntax error)
    if (CALC_line[0] == 'x' || CALC_line[0] == '/' ||
        CALC_line[0] == 'E' || CALC_line[0] == '.' ||
        CALC_line[0] == '-' || CALC_line[0] == '+' ){
        return 0;
    }
    else {
        return 1;
    }
}
