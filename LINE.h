/*
 * LINE.h
 *
 * Created on: 25 Jan 2021
 *      Author: Hélios Aël Lyons
 *      Supervisor: Dr. Lotfi Mhamdi
 */

// 0. Global Variable
extern char CALC_line[];

// 1. Function Prototypes
void LINE_counter(void);
void LINE_counterReset(void);
void LINE_track(char newChar);
void LINE_trackReset(void);
int LINE_validate_num(void);
int LINE_validate_firstOp(void);

