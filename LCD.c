/*
 * CALC.h
 *
 * Created on: 18 Jan 2021
 *      Author: Hélios Aël Lyons
 *
 */

// 1. Preprocessor Directives Section
#include <LCD.h>
#include <PLL.h>

// Research sources for parsing and applying the HD44780U Datasheet:
// - https://mil.ufl.edu/3744/docs/lcdmanual/commands.html
// - https://dawes.wordpress.com/2010/01/05/hd44780-instruction-set/

// 2. Subroutines section

// Subroutine to send an enable pulse to the LCD
// LCD_E is the enable pin, starts read/write
// see HD44780U datasheet (p. 5) for LCD port definitions
void LCD_Pulse(void){
    LCD_E |= 0x04;
    //SysTick_Wait(2);
    LCD_E &= ~0x04;
    //SysTick_Wait(2);
}

// Subroutine to send instructions to the LCD
// Data is written to GPIO_PORTB_DATA_R, corresponding to ports PB0 - PB3
// see HD44780U datasheet (p. 28) for instruction codes
// LCD_RS selects the instruction register
void LCD_Cmd(char cmd){ // see HD44780U datasheet (p. 24-25)
    LCD_RS = 0x00; // PA3 low, RS set to instruction input

    char nibble1 = cmd & 0x0F; // mask MSBs of byte
    char nibble2 = (cmd & 0xF0) >> 4; // mask LSBs of byte

    GPIO_PORTB_DATA_R = nibble2; // send MSBs
    LCD_Pulse();
    GPIO_PORTB_DATA_R = nibble1; // send LSBs
    LCD_Pulse();
}

// Subroutine to print a nibble onto the LCD
// Data is written to GPIO_PORTB_DATA_R, corresponding to ports PB0 - PB3
// see HD44780U datasheet (p. 17, 18) for character codes
// LCD_RS selects the data register
void LCD_Print_Nibble(char nibble){
    LCD_RS = 0x08; // PA3 high, RS set to data input
    GPIO_PORTB_DATA_R = nibble;
    LCD_Pulse();
}

// Subroutine to print a byte onto the LCD
// Data is written to GPIO_PORTB_DATA_R, corresponding to ports PB0 - PB3
// see HD44780U datasheet (p. 17, 18) for character codes
// LCD_RS selects the data register
// First 2 lines mask 4 MSBs and 4 LSBs to separate into nibbles
void LCD_Print_Byte(char byte){
    char nibble1 = byte & 0x0F; // mask first 4 characters of byte
    char nibble2 = (byte & 0xF0) >> 4; // mask last 4 characters of byte
    LCD_Print_Nibble(nibble2); // print second nibble first, as LCD expects MSBs first
    LCD_Print_Nibble(nibble1); // print first nibble for LCD LSBs
}

// Subroutine to initialise the LCD
// see HD44780U datasheet (p. 46) for notes on 4-bit initialisation
// LCD_E is the enable pin
// LCD_RS selects the instruction or data registers
void LCD_Init(void){
    LCD_RS = 0x00; // RS & E low for initialisation
    LCD_E = 0x00;

    //SysTick_Wait(3200000); // Wait for >40 ms after VCC rises to 2.7 V
    LCD_Cmd(0x03);           // 80 MHz = 12.5 ns time unit, so 12.5ns * 3200000 = 40 ms delay
    //SysTick_Wait(340000);  // Wait for >4.1 ms
    LCD_Cmd(0x03);
    //SysTick_Wait(12000);   // Wait for >100 us
    LCD_Cmd(0x03);

    LCD_Cmd(0x02); // Set DB5 to high (set interface to 4 bits)
    LCD_Cmd(0x02);
    LCD_Cmd(0x08); // Set DB5, DB6, DB7 –– DB7 sets line #, DB6 sets 5x8 or 5x10 dot matrix size
    LCD_Cmd(0x00); // 0x08 nibble (1000) represents 2 line display with 5x8 matrix size
    LCD_Cmd(0x08); // Set DB7 high
    LCD_Cmd(0x00); // All low
    LCD_Cmd(0x01); // Set DB4 high
    LCD_Cmd(0x00); // All low
    LCD_Cmd(0x06); // ID=1 (increment)
}

void LCD_Syntax(void){
    LCD_Cmd(0x01); // clear LCD
    LCD_Print_Byte('S'); // send error message
    LCD_Print_Byte('Y'); // pres C to clear
    LCD_Print_Byte('N');
    LCD_Print_Byte('T');
    LCD_Print_Byte('A');
    LCD_Print_Byte('X');
    LCD_Print_Byte(' ');
    LCD_Print_Byte('E');
    LCD_Print_Byte('R');
    LCD_Print_Byte('R');
    LCD_Print_Byte('O');
    LCD_Print_Byte('R');
}

void LCD_Tests(void){
    LCD_Print_Byte('U');
    LCD_Print_Byte('S');
    LCD_Print_Byte('E');
    LCD_Print_Byte(' ');
    LCD_Print_Byte('T');
    LCD_Print_Byte('E');
    LCD_Print_Byte('S');
    LCD_Print_Byte('T');
    LCD_Print_Byte('S');
}

// Subroutine to initialise port A & B pins for LCD output
// Inputs: None
// Output: PB0-PB4 are the 4 bit data outputs, PA2-PA3 are the 2 control outputs
// Notes: These six TIVA pins are connected to virtual LCD pins on TinaCloud
void LCD_Port_Init(void){
    // PORT A Initialisation
    SYSCTL_RCGCGPIO_R |= 0x00000001;  // 1. Activate Port A
        while((SYSCTL_PRGPIO_R & 0x00000001)==0){}; // Delay
    GPIO_PORTA_LOCK_R = 0x4C4F434B;   // 2. Unlocks GPIO_CR register
    GPIO_PORTA_CR_R = 0x0C;           // Allow changes PA2, PA3
    GPIO_PORTA_AMSEL_R = 0x00;        // 3. Disable analogue functions
    GPIO_PORTA_PCTL_R = 0x00000000;   // 4. GPIO clear bit PCTL
    GPIO_PORTA_DIR_R = 0x0C;          // 5. Set PA2, PA3 output
    GPIO_PORTA_AFSEL_R = 0x00;        // 6. No alternate functions
    GPIO_PORTA_DEN_R = 0x0C;          // 7. Enable digital pins PA2, PA3

    // PORT B Initialisation
    SYSCTL_RCGCGPIO_R |= 0x00000002;  // 1. Activate Port B
        while((SYSCTL_PRGPIO_R & 0x00000002)==0){}; // Delay
    GPIO_PORTB_LOCK_R = 0x4C4F434B;   // 2. Unlocks GPIO_CR register
    GPIO_PORTB_CR_R = 0x0F;           // Allow changes to PB0 to PB3
    GPIO_PORTB_AMSEL_R = 0x00;        // 3. Disable analogue functions
    GPIO_PORTB_PCTL_R = 0x00000000;   // 4. GPIO clear bit PCTL
    GPIO_PORTB_DIR_R = 0x0F;          // 5. Set PB0 to PB3 to output
    GPIO_PORTB_AFSEL_R = 0x00;        // 6. No alternate functions
    GPIO_PORTB_DEN_R = 0x0F;          // 7. Enable digital pins PB0 to PB3
}

void LCD_noInput(void){
    LCD_Print_Byte('N');
    LCD_Print_Byte('O');
    LCD_Print_Byte(' ');
    LCD_Print_Byte('I');
    LCD_Print_Byte('N');
    LCD_Print_Byte('P');
    LCD_Print_Byte('U');
    LCD_Print_Byte('T');
}
