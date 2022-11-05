/*
 * button.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Asus
 */


#include "button.h"
#include "timer.h"

int KeyReg0_RS = NORMAL_STATE;
int KeyReg1_RS = NORMAL_STATE;
int KeyReg2_RS = NORMAL_STATE;

int KeyReg0_INC = NORMAL_STATE;
int KeyReg1_INC = NORMAL_STATE;
int KeyReg2_INC = NORMAL_STATE;

int KeyReg0_DEC = NORMAL_STATE;
int KeyReg1_DEC = NORMAL_STATE;
int KeyReg2_DEC = NORMAL_STATE;

int KeyReg3_RS = NORMAL_STATE;
int KeyReg3_INC = NORMAL_STATE;
int KeyReg3_DEC = NORMAL_STATE;

int TimeOutForKeyPress =  300;

int button0_flag = 0;
int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;
int button4_flag = 0;

int isButtonPressed_INC(){
	if(button1_flag == 1){
		button1_flag = 0;
		return 1;
	}
	return 0;
}
int isButtonPressed_DEC(){
	if(button2_flag == 1){
		button2_flag = 0;
		return 1;
	}
	return 0;
}
int isButtonPressed_RS(){
	if(button0_flag == 1){
		button0_flag = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed_INC(){
	if(button3_flag == 1){
		button3_flag = 0;
		return 1;
	}
	return 0;
}
int isButtonLongPressed_DEC(){
	if(button4_flag == 1){
		button4_flag = 0;
		return 1;
	}
	return 0;
}


void subKeyProcess(){
	if(KeyReg3_INC == PRESSED_STATE){
		button1_flag = 1;
	}
	if(KeyReg3_DEC == PRESSED_STATE){
		button2_flag = 1;
	}
	if(KeyReg3_RS == PRESSED_STATE){
		button0_flag = 1;
	}

}
void subKeyButtonLongPressed(){
	if(KeyReg3_INC == PRESSED_STATE){
		button3_flag = 1;
	}
	if(KeyReg3_DEC == PRESSED_STATE){
		button4_flag = 1;
	}
}

void getKeyInput(){
  KeyReg0_RS = KeyReg1_RS;
  KeyReg1_RS = KeyReg2_RS;
  KeyReg2_RS = HAL_GPIO_ReadPin(RESET_GPIO_Port, RESET_Pin);

  KeyReg0_INC = KeyReg1_INC;
  KeyReg1_INC = KeyReg2_INC;
  KeyReg2_INC = HAL_GPIO_ReadPin(INC_GPIO_Port, INC_Pin);

  KeyReg0_DEC = KeyReg1_DEC;
  KeyReg1_DEC = KeyReg2_DEC;
  KeyReg2_DEC = HAL_GPIO_ReadPin(DEC_GPIO_Port, DEC_Pin);

  if ((KeyReg1_INC == KeyReg0_INC) && (KeyReg1_INC ==  KeyReg2_INC)){
    if (KeyReg3_INC != KeyReg2_INC){
    	KeyReg3_INC =   KeyReg2_INC;
    	if( KeyReg2_INC == PRESSED_STATE){
    		TimeOutForKeyPress = 300;
    		subKeyProcess();
    	}
    }
    else{
    	TimeOutForKeyPress--;
        if (TimeOutForKeyPress == 0){
        	if( KeyReg2_INC == PRESSED_STATE){
        		subKeyButtonLongPressed();
        	}
        	TimeOutForKeyPress = 300;
        }
    }
  }


  if ((KeyReg1_DEC == KeyReg0_DEC) && (KeyReg1_DEC == KeyReg2_DEC)){
    if (KeyReg3_DEC != KeyReg2_DEC){
    	KeyReg3_DEC = KeyReg2_DEC;
    	if(KeyReg2_DEC == PRESSED_STATE){
    		TimeOutForKeyPress = 300;
    		subKeyProcess();
    	}
    }else{
    	TimeOutForKeyPress--;
        if (TimeOutForKeyPress == 0){
        	if( KeyReg2_DEC == PRESSED_STATE){
        		subKeyButtonLongPressed();
        	}
        	TimeOutForKeyPress = 300;
        }
    }
  }

  if ((KeyReg1_RS == KeyReg0_RS) && (KeyReg1_RS == KeyReg2_RS)){
    if (KeyReg3_RS != KeyReg2_RS){
    	KeyReg3_RS = KeyReg2_RS;
    	if(KeyReg2_RS == PRESSED_STATE){
    		TimeOutForKeyPress = 200;
    		subKeyProcess();
    	}
    }else{
    	TimeOutForKeyPress--;
        if (TimeOutForKeyPress == 0){
        	KeyReg3_RS = NORMAL_STATE;
        }
    }
  }

  if(KeyReg3_INC == PRESSED_STATE && KeyReg3_DEC == PRESSED_STATE && KeyReg3_RS == PRESSED_STATE){
	  TimeOutForKeyPress--;
      if (TimeOutForKeyPress == 0){
      	KeyReg3_RS = NORMAL_STATE;
      }
  }
}
