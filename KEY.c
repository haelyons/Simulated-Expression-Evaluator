/*
 * STACK.c
 *
 * Created on: 24 Jan 2021
 *      Author: Hélios Aël Lyons
 *
 */

// 1. Preprocessor Directives
#include <KEY.h>
#include <PLL.h>
#include <LCD.h>

#include <stdio.h>

// Keypad Matrix Layout
// COL1 COL2 COL3  COL4
//   1    2    3    A   ROW 1
//   4    5    6    B   ROW 2
//   7    8    9    C   ROW 3
//   *    0    #    D   ROW 4

// Shift Key Designation
//   NO-SHIFT   SHIFT
// A     +        x
// B     -        /
// C     .        E
// D   SHIFT    SHIFT


// 2. Variables
unsigned char KEY_Map[4][4] = {{'1','2','3','+'},
                               {'4','5','6','-'},
                               {'7','8','9','.'},
                               {'=','0','C','S'}};

unsigned char KEY_Shift_Map[4][4] = {{'1','2','3','x'},
                                     {'4','5','6','/'},
                                     {'7','8','9','E'},
                                     {'=','0','C','S'}};

int shift = 0;
int repeat = 0;

// 3. Subroutines Section
// Source: https://www.gammon.com.au/forum/?id=14175

// Subroutine to detect the coordinates of keypresses on the matrix keypad
// Inputs: COLUMNS (PD0-PD3) are iteratively read to check if they go high
// Outputs: ROWS (PE0-PE3) are iteratively stead to high to affect COLUMN state
// 1U << 1 is C specific syntax describing, i.e 0010; a simple way to iterate through ROWS & COLS
// There are 2 flags, as well as more processed in main: SHIFT & REPEAT.
char KEY_Scan(void) {

      int row = 0;
      for(int i = 0; i <= 3; i++, row++) { // iterate through rows

          int col = 0;
          ROWS = (1U << i); // bit shift through PE0-PE3 ports –– 1U << 2 = 0100

          for (int n = 0; n <= 3; n++, col++) { // iterate through columns

              if ((COLUMNS & 0x0F) & (1U << n)) { // unsigned int bit set HIGH @ n
                  ROWS = 0;
                  if (repeat) {
                      return 'R';
                  }

                  else {
                      repeat = 1;

                      if (shift) {
                          shift = 0; // shift is only active till the next key is pressed
                          return KEY_Shift_Map[row][col];
                      }

                      else {
                          if (KEY_Map[row][col] == 'S') { // if Shift is pressed
                              shift = 1; // set shift to high
                          }
                          return KEY_Map[row][col]; // return relevant char
                      }
                  }
              }
          }
      }
      // if the end of the loop is reached, nothing has been pressed, so break
      repeat = 0;
      return 'R';
}
// This text was essential to understanding matrix keypad functionality, and ways to extend this with
// diodes to avoid ghost presses. While diodes were not necessary in this design, the logic
// in the article informed the design of the above function KEY_scan(), though no code was reproduced.

// Citation (IEEE):
// Gammon, N., 2018. Using A Keypad Matrix. [online] Gammon.com.au.
// Available at: <https://www.gammon.com.au/forum/?id=14175> [Accessed 15 December 2020].


// Subroutine to initialise port D & E pins for KEYPAD input
// Input: PD0-PD3 (COLUMNs)
// Output: PE0-PE3 (ROWs)
// Notes: These six TIVA pins are connected to a simulated keypad schematic in TINACloud
void KEY_Port_Init(void){
    // PORT D Initialisation for COLUMNs (input)
    SYSCTL_RCGCGPIO_R |= 0x00000008;  // 1. Activate Port D
        while((SYSCTL_PRGPIO_R & 0x00000008)==0){}; // Delay
    GPIO_PORTD_LOCK_R = 0x4C4F434B;   // 2. Unlocks GPIO_CR register
    GPIO_PORTD_CR_R = 0x0F;           // Allow changes PD0 to PD3
    GPIO_PORTD_AMSEL_R = 0x00;        // 3. Disable analogue functions
    GPIO_PORTD_PCTL_R = 0x00000000;   // 4. GPIO clear bit PCTL
    GPIO_PORTD_DIR_R = 0x00;          // 5. PD0-PD3 set to input
    GPIO_PORTD_AFSEL_R = 0x00;        // 6. No alternate functions
    GPIO_PORTD_DEN_R = 0x0F;          // 7. Enable digital pins PD0 - PD3

    // PORT E Initialisation for ROWs (output)
    SYSCTL_RCGCGPIO_R |= 0x00000010;  // 1. Activate Port E clock – datasheet, RCGCGPIO
        while((SYSCTL_PRGPIO_R & 0x00000010)==0){}; // Delay
    GPIO_PORTE_LOCK_R = 0x4C4F434B;   // 2. Unlocks GPIO_CR register
    GPIO_PORTE_CR_R = 0x0F;           // Allow changes to PE0 to PE3
    GPIO_PORTE_AMSEL_R = 0x00;        // 3. Disable analogue functions
    GPIO_PORTE_PCTL_R = 0x00000000;   // 4. GPIO clear bit PCTL
    GPIO_PORTE_DIR_R = 0x0F;          // 5. Set PE0 to PE3 to output
    GPIO_PORTE_AFSEL_R = 0x00;        // 6. No alternate functions
    GPIO_PORTE_DEN_R = 0x0F;          // 7. Enable digital pins PE0 to PE3
}
