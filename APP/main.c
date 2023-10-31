/*
 * main.c
 *
 *  Created on: Aug 22, 2023
 *      Author: hedra
 */
#include"../LIB/BIT_Math.h"
#include"../LIB/STD_Types.h"
#include"../MCAL/DIO/DIO_interface.h"
#include"../HAL/Keypad/KYEPAD.h"
#include"../HAL/LCD/LCD.h"
#include"Stopwatch.h"
#include"avr/delay.h"

int main(void)
{
	DIO_voidInit();
	LCD_voidInit();
	KPD_voidInit();

	uint8 u8KeypadPressedKey=0xFF;
	LCD_voidSendString(0,"00:00:00");

	while(1)
	{
		u8KeypadPressedKey=KPD_u8GetPressedKey();
		while(u8KeypadPressedKey != '7' &&  u8KeypadPressedKey!= '9'
				&& u8KeypadPressedKey!= '+' && u8KeypadPressedKey!= '-' && u8KeypadPressedKey!= '=')
		{
			u8KeypadPressedKey=KPD_u8GetPressedKey();
		}

		switch(u8KeypadPressedKey)
		{
		case '7':
			LCD_voidMoveRight();
			break;
		case '9':
			LCD_voidMoveLeft();
			break;
		case'+':
			LCD_voidIncrement();
			break;
		case'-':
			LCD_voidDecrement();
			break;
		case '=':
			LCD_voidTime();
			break;
		}
	}

}

