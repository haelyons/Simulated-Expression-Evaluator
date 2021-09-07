/*
 * CHAR.c
 *
 *  Created on: 27 Jan 2021
 *      Author: helios
 */

int top = -1;
char stack[20];
int size = 20;


void CH_init(void) {
    for(int i = 0; i < size; i++){
        stack[i] = '0';
    }
    top = -1;
}

int CH_empty(void) {

   if(top == -1) { return 1; }
   else { return 0; }
}

int CH_full(void) {

   if(top == size) { return 1; }

   else { return 0; }
}

char CH_peek(void) {
   return stack[top];
}

int CH_pop(void) {
   double data;

   if(!CH_empty()) {
      data = stack[top];
      top = top - 1;
      return 1;
   }
   else {
      return 0;
   }
}

int CH_push(char data) {

   if(!CH_full()) {
      top++;
      stack[top] = data;
      return 1;
   }
   else {
      return 0;
   }
}
