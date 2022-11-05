/*
 * fsm_button_run.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Asus
 */

#include "fsm_button_run.h"
#include "button.h"
#include "main.h"
#include "timer.h"
#include "global.h"

enum state {NORMAL,INCREASE,DECREASE,COUNTDOWN};

enum state currentState = NORMAL;
enum state nextState = NORMAL;

int num = 0;

void fsm_simple_buttons_run(){
	currentState = nextState;  // trang thai bat dau
	display7SEG(num);
	switch(currentState){
		case NORMAL:
			// sau 10s khong co nut nao nhan thi chuyen qua trang thai COUNTDOWN
			if(timer4_flag == 1){
				nextState = COUNTDOWN;
				setTimer3(1);
			}
			if(isButtonPressed_INC()){ // nut INC duoc nhan
				num++;
				if(num > 9) num = 0;
				display7SEG(num);
				setTimer4(1000);
			}
			if(isButtonPressed_DEC()){ // nut DEC duoc nhan
				num--;
				if(num < 0) num = 9;
				display7SEG(num);
				setTimer4(1000);
			}
			if(isButtonPressed_RS()){ // nut RESET duoc nhan
				num = 0;
				display7SEG(num);
			}
			if(isButtonLongPressed_INC()){ // nhan giu nut INC thì chuyen qua trang thai INCREASE
				nextState = INCREASE;
				setTimer2(100);
				setTimer4(1000);
			}
			if(isButtonLongPressed_DEC()){// nhan giu nut INC thì chuyen qua trang thai DECREASE
				nextState = DECREASE;
				setTimer2(100);
				setTimer4(1000);
			}
			break;
		case INCREASE:
			// sau 10s khong co nut nao nhan thi chuyen qua trang thai COUNTDOWN
			if(timer4_flag == 1){
				nextState = COUNTDOWN;
				setTimer3(1);
			}
			// sau 3s nhan giu thi gia tri se tang len 1 don vi sau 1s
			if(isButtonLongPressed_INC() && timer2_flag == 1){
				num++;
				if(num > 9) num = 0;
				display7SEG(num);
				setTimer2(100);
				setTimer4(1000);
			}
			 // nut INC duoc nhan va duoc chuyen qua trang thai NORMAL
			if(isButtonPressed_INC()){
				num++;
				if(num > 9) num = 0;
				display7SEG(num);
				nextState = NORMAL;
				setTimer4(1000);
			}
			// nut DEC duoc nhan va duoc chuyen qua trang thai NORMAL
			if(isButtonPressed_DEC()){
				num--;
				if(num < 0) num = 9;
				display7SEG(num);
				nextState = NORMAL;
				setTimer4(1000);
			}
			// nut RESET duoc nhan va duoc chuyen qua trang thai NORMAL
			if(isButtonPressed_RS()){
				num = 0;
				display7SEG(num);
				nextState = NORMAL;
			}
			break;
		case DECREASE:
			// sau 10s khong co nut nao nhan thi chuyen qua trang thai COUNTDOWN
			if(timer4_flag == 1){
				nextState = COUNTDOWN;
				setTimer3(1);
			}
			// sau 3s nhan giu thi gia tri se giam len 1 don vi sau 1s
			if(isButtonLongPressed_DEC() && timer2_flag == 1){
				num--;
				if(num < 0) num = 9;
				display7SEG(num);
				setTimer2(100);
				setTimer4(1000);
			}
			// nut INC duoc nhan va duoc chuyen qua trang thai NORMAL
			if(isButtonPressed_INC()){
				num++;
				if(num > 9) num = 0;
				display7SEG(num);
				nextState = NORMAL;
				setTimer4(1000);
			}
			// nut DEC duoc nhan va duoc chuyen qua trang thai NORMAL
			if(isButtonPressed_DEC()){
				num--;
				if(num < 0) num = 9;
				display7SEG(num);
				nextState = NORMAL;
				setTimer4(1000);
			}
			// nut RESET duoc nhan va duoc chuyen qua trang thai NORMAL
			if(isButtonPressed_RS()){
				num = 0;
				display7SEG(num);
				nextState = NORMAL;
			}
			break;
		case COUNTDOWN:
			// sau 10s gia tri se auto giam xuong 1 don vi sau moi giay cho den 0 thi dung
			if(timer3_flag == 1){
				num--;
				if(num < 0) num = 0;
				display7SEG(num);
				setTimer3(100);
			}
			// nut INC duoc nhan va duoc chuyen qua trang thai NORMAL
			if(isButtonPressed_INC()){
				num++;
				if(num > 9) num = 0;
				display7SEG(num);
				nextState = NORMAL;
				setTimer4(1000);
			}
			// nut DEC duoc nhan va duoc chuyen qua trang thai NORMAL
			if(isButtonPressed_DEC()){
				num--;
				if(num < 0) num = 9;
				display7SEG(num);
				nextState = NORMAL;
				setTimer4(1000);
			}
			// nut RESET duoc nhan va duoc chuyen qua trang thai NORMAL
			if(isButtonPressed_RS()){
				num = 0;
				display7SEG(num);
				nextState = NORMAL;
			}
			// nhan giu nut INC thì chuyen qua trang thai INCREASE
			if(isButtonLongPressed_INC()){
				nextState = INCREASE;
				setTimer2(100);
				setTimer4(1000);
			}
			// nhan giu nut INC thì chuyen qua trang thai DECREASE
			if(isButtonLongPressed_DEC()){
				nextState = DECREASE;
				setTimer2(100);
				setTimer4(1000);
			}
			break;
		default:
			break;

	}
}
