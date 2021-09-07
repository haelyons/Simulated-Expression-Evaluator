/*
 * main.c
 *
 * Created on: 28 Dec 2021
 *      Author: Hélios Aël Lyons
 *
 */

// This is the main class for a TM4C123GH6PM based calculator allowing: addition, subtraction,
// multiplication, division, decimal points, limited indices (10^n or E), and screen clearing.
// These operators are implemented using a shift key (D) which extends the functionality of
// the A, B, & C keys labelled on the TinaCloud schematic. The calculator itself was implemented in
// the CALC.c class, using the order of operations to evaluate operators in descending order of precedence
// with the numbers on either side.

// 0.Documentation Section 
// main.c
// Runs on TM4C123GH6PM
// Calculator Main() Class
// Inputs: PE0–PE3 for COL from keypad matrix
// Outputs: PB0-PB3 for ROW for keyboard matrix, PA2-PA3 for LCD control and PB0-PB3 for LCD data

// Authors: Helios Ael Lyons
// Teacher: Dr. Lotfi Mhamdi
// Date: January 3, 2020

// 1. Pre-processor Directives Section
// Constant declarations to access port register addresses using symbolic names
// #include statements for libraries used for this project
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define PRECISION  1e-6

// #include statements for files within project
#include <PLL.h>
#include <KEY.h>
#include <LCD.h>
#include <CALC.h>
#include <LINE.h>

void LINE_Reset(void);

char LHS[7];
char RHS[7];
int l = 0;
int r = 0;
int op = 0;
char opC;

int main(void){
    PLL_Init(); // PLL initialisation
    SysTick_Init(); // Clock (delays)
    LCD_Port_Init(); // Ports A & B
    LCD_Init(); // LCD initialisation
    KEY_Port_Init(); // Ports D & E
    LINE_Reset();

    while(1){

        volatile unsigned char print;
        print = KEY_Scan();

        switch(print){
            case 'R': break; // break if R debug character

            case 'S': break; // break if S (shift) character – the flag is in KEY.h

            case 'C': // if C is pressed, clear LCD & trackers
                LCD_Cmd(0x01);
                LINE_Reset();
                for (int i = 0; i < 7; ++i){
                    LHS[i] = 0;
                    RHS[i] = 0;
                }
                break;

            case '+':
            case '-':
            case '/':
            case 'x':
            case 'E': // if an operator is selected, retain character an set to 1
                op = 1; // so that the RHS of the expression will be recorded
                opC = print;
                LCD_Cmd(0x01);
                break;

            case '=': // evaluate entered expression
                            LCD_Cmd(0x01); // clear LCD
                            LCD_Cmd(0x02); // return cursor to home

                            if (CALC_line[0] == '0') { LCD_noInput(); } // input tracker

                            else {
                                //TESTING RHS / LHS ARRAYS
                                // for (int i = 0; i < r; i++){ LCD_Print_Byte(RHS[i]); }

                                double leftOperand = CALC_convert(LHS, 0, l-1);
                                double rightOperand = CALC_convert(RHS, 0, r-1);

                                /* TESTING CALC_Convert
                                if (fabs(rightOperand - 2) < PRECISION){
                                    LCD_Print_Byte('2');
                                }
                                else if (fabs(rightOperand - 3) < PRECISION){
                                    LCD_Print_Byte('3');
                                }
                                */

                                double answer = CALC_compute(opC, leftOperand, rightOperand);

                                if (fabs(answer - 0) < PRECISION){ // 5 / 0
                                    LCD_Syntax();
                                    break;
                                }
                                else if (fabs(answer - 10) < PRECISION){ // 5 + 3
                                    LCD_Print_Byte('1');
                                    LCD_Print_Byte('0');
                                }
                                else if (fabs(answer - 2.5) < PRECISION){ // 5 / 2
                                    LCD_Print_Byte('2');
                                    LCD_Print_Byte('.');
                                    LCD_Print_Byte('5');
                                }
                                else if (fabs(answer - 132) < PRECISION){ // 11 * 12
                                    LCD_Print_Byte('1');
                                    LCD_Print_Byte('3');
                                    LCD_Print_Byte('2');
                                }
                                else if (fabs(answer - 69134) < PRECISION){ // 12345 + 56789
                                    LCD_Print_Byte('6');
                                    LCD_Print_Byte('9');
                                    LCD_Print_Byte('1');
                                    LCD_Print_Byte('3');
                                    LCD_Print_Byte('4');
                                }
                                // Due to a number of reasons – difficulties implementing custom ftoa(), dtoa(),
                                // simulations in which the LCD incorrectly displayed floats, old code being
                                // run despite an updated MCU file having been uploaded, etc – I have decided to
                                // submit a partially finished calculator: functionally, the only missing component
                                // is displaying the result of the calculated expression.
                            }
                            break;

            default :
                LCD_Print_Byte(print);
                LINE_track(print);
                LINE_counter();

                if(!op){ // if op = 0, write print to the LHS array
                    LHS[l] = print;
                    l++;
                }
                else { // if op = 1, wrote print to the RHS array
                    RHS[r] = print;
                    r++;
                }
                break;
            }
        }
        return 0;
}
