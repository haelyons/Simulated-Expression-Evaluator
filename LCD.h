/*
 * LCD.h
 *
 * Created on: 18 Jan 2021
 *      Author: Hélios Aël Lyons
 *
 */

#ifndef LCD_H_
#define LCD_H_

// 1. Pre-processor Directives Section
// Constant declarations to access port register addresses using symbolic names

// PORT A –– RS & E on LCD (PA2,PA3)
#define GPIO_PORTA_DATA_R       (*((volatile unsigned char *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
// GPIO_PORTA_PUR unnecessary as TINACloud does not support pullup resistors

// PORT B –– 4 bit TIVA output (PB0-PB3) going to LCD input (DB4-DB7)
#define GPIO_PORTB_DATA_R       (*((volatile unsigned char *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

// PORT A –– RS & E pin specific addresses
#define LCD_E                  (*((volatile unsigned long *)0x40004010)) // PA2
#define LCD_RS                 (*((volatile unsigned long *)0x40004020)) // PA3

// PORT B – Data register
#define GPIO_PORTB_DATA_R       (*((volatile unsigned char *)0x400053FC))

// 2. Function Prototypes
void LCD_Port_Init(void);
void LCD_Init(void);
void LCD_Pulse(void);
void LCD_Cmd(char cmd);
void LCD_Print_Nibble(char nibble);
void LCD_Print_Byte(char byte);
void LCD_Syntax(void);
void LCD_Tests(void);
void LCD_noInput(void);

#endif /* CALC_H_ */
