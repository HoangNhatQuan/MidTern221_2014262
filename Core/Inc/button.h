/*
 * button.h
 *
 *  Created on: Nov 5, 2022
 *      Author: Asus
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"
#include "global.h"

#define NORMAL_STATE 	GPIO_PIN_SET
#define PRESSED_STATE  	GPIO_PIN_RESET


int isButtonPressed_INC();
int isButtonPressed_DEC();
int isButtonPressed_RS();
int isButtonLongPressed_INC();
int isButtonLongPressed_DEC();

void isButtonLongPressed();
void subKeyProcess();
void getKeyInput();


#endif /* INC_BUTTON_H_ */
