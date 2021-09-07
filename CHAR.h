/*
 * CHAR.h
 *
 *  Created on: 27 Jan 2021
 *      Author: helios
 */

#ifndef CHAR_H_
#define CHAR_H_

#include <stdio.h>

void CH_init(void);
int CH_empty(void);
int CH_full(void);
int CH_push(char data);
int CH_pop(void);
char CH_peek(void);

#endif /* CHAR_H_ */
