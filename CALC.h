/*
 * CALC.h
 *
 * Created on: 18 Jan 2021
 *      Author: Hélios Aël Lyons
 *
 */

#ifndef CALC_H_
#define CALC_H_

#include <stdio.h>
#include <math.h>


char CALC_operand(char num);
double CALC_compute(char c, double num1, double num2);
double CALC_convert(const char* array, int start, int stop);

// DEPRECATED DUE TO NON-FUNCTIONAL INFIX EVALUATOR FUNCTION
//int CALC_order(char op);
//double CALC_evaluate(char exp[]);

#endif /* CALC_H_ */
