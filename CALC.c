/*
 * CALC.c
 *
 * Created on: 18 Jan 2021
 *      Author: Hélios Aël Lyons,
 *
 */

// Sources used to inform evaluator design:

// The below introduces the concept of a binary expression tree, loosely followed in this implementation
// https://www.rhyscitlema.com/algorithms/expression-parsing-algorithm/#Using-right-associative-operators

// A recursive implementation was also explored (^) though not implemented due to its complexity
// https://www.geeksforgeeks.org/all-ways-to-add-parenthesis-for-evaluation/

// The algorithm was closely modelled on the source below, a stack based INFIX expression evaluator,
// which is what this class does, though the lack of easily available dynamic data structures in C made
// it quite difficult to implement something similar. Infix notation refers to operators being placed
// between operands. This simplifies input processing – e.g no longer having to account for -ve signs
// as first input – and provides a simpler overall algorithm (see code length for provided sources).
// https://gist.github.com/raviteja1452/8632e6460edc05350f8eacab367452b5

#include <ctype.h>

#include <CALC.h>
#include <LINE.h>
/*
void CALC_stacks(void){
    DB_init();
    CH_init();
}

int CALC_order(char op) { // establish order of precedence
    switch (op) { // higher int = higher precedence, following order of operations (IDMAS)
        case '+':
        case '-':
            return 1;
        case 'x':
        case '/':
            return 2;
        case 'E':
            return 3;
    }
    return -1;
}
*/

char CALC_operand(char current) { // check if the input value is an operand (including decimal points)
    if ((current >= '0' && current <= '9') || current == '.'){ // chars can be directly compared
        return 1;
    }
    else {
        return 0;
    }
}

double CALC_compute(char op, double num1, double num2) {
    double result;
    switch (op) { // take 2 doubles and compute result with switch

    case '+':
        result = num1 + num2;
        return result;

    case '-':
        result = num1 - num2;
        return result;

    case 'x':
        result = num1 * num2;
        return result;

    case '/':
        if (num2 > 0){
            result = num1 / num2;
            return result;
        }
        return 0;

    case 'E':
        result = (num1 * pow(10, num2)); // pow used for E from <math.h> library
        return result;

    default:
        result = -1;
    }
    return 0;
}

// This method was directly pulled from StackOverflow to be able to convert char arrays into
// doubles, as I struggled to write my own atof() function.
// https://stackoverflow.com/questions/15583965/c-convert-section-of-char-array-to-double
double CALC_convert(const char* array, int start, int stop) {
    unsigned long long int m = 1;
    double ret = 0;
    for (int i = stop; i >= start; i--) {
        ret += (array[i] - '0') * m; // conversion to ASCII ( - '0' )
        m *= 10;
    }
    return ret;
}

// DEPRECATED CALC_evaluate()
// Intended to calculate the result of an infix expression using arrays to sort operands
// and operators according to their order of precedence. Not fully functional and so replaced
// with basic calculator functionality.
/*
double CALC_evaluate(char expression[]) {
    double numbers[5]; // maximum possible number of operands & operators in 1 expression – 8 each
    char operators[5];
    char buffer[8]; // total number of characters in 1 line (and only 1 is used for this evaluator)

    int numTrack = 0; // tracker for numbers, used to address number array
    int opTrack = 0; // tracker for operators, used to address operator array
    int initial = 0;
    int i = 0;
    char current;

    // This while loop is divided into detecting operands, and operators, separating them
    // into arrays (operators[] and numbers[]) based on their type
    // ['5','x','5']
    while ((current = expression[i]) != '0') { // check if first value in expression doesn't equal 0
        if (CALC_operand(current)) { // check if current is an operand

            buffer[initial++] = current; // if it is, assign it to the next buffer spot

            if (!CALC_operand(expression[i++])) { // if the next value is not an operand

                buffer[initial] = 0; // reset initial and its buffer element
                initial = 0;
                sscanf(buffer, "%lf", &numbers[numTrack++]); // get numbers from the buffer
            }                                                // and add them to the number array
                                                             // using the number tracker
        }
        else {

            while ((opTrack > 0) && (CALC_order(current) <= CALC_order(operators[opTrack - 1]))) {
                // use the tracker
                numbers[numTrack - 2] = CALC_compute(operators[opTrack - 1],
                                                       numbers[numTrack - 2],
                                                       numbers[numTrack - 1]);
                opTrack--;
                numTrack--;
            }
            operators[opTrack++] = current;
        }
        i++;
    }
    while (opTrack > 0) {
        numbers[numTrack - 2] = CALC_compute(operators[opTrack - 1],
        numbers[numTrack - 2], numbers[numTrack - 1]);
        opTrack--;
        numTrack--;
    }
    return numbers[0];
}
*/
