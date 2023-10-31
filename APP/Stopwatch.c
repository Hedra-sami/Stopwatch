/*
 * Stopwatch.c
 *
 *  Created on: Aug 22, 2023
 *      Author: hedra
 */
#include"../LIB/BIT_Math.h"
#include"../LIB/STD_Types.h"
#include"../MCAL/DIO/DIO_interface.h"
#include"../HAL/Keypad/KYEPAD.h"
#include"../HAL/LCD/LCD.h"
#include"avr/delay.h"


uint8 u8hour=0;
uint8 u8minute=0;
uint8 u8sec=0;
uint8 u8MoveCursor=4;
uint8 u8flag=0;
uint8 u8checksec=0;




void LCD_voidMoveRight(void){

	if(u8MoveCursor==5)
		{
			u8MoveCursor=(u8MoveCursor-1+2)%6;
			LCD_voidMoveCourser(0,0,u8MoveCursor);
		}
	else
		{
			u8MoveCursor=(u8MoveCursor+2)%6;
			if(u8MoveCursor==0)
				LCD_voidMoveCourser(0,0,u8MoveCursor+1);
			else if(u8MoveCursor==2)
				LCD_voidMoveCourser(0,0,u8MoveCursor+2);
			else if(u8MoveCursor==4)
				LCD_voidMoveCourser(0,0,u8MoveCursor+3);

		}

}
void LCD_voidMoveLeft(void){

	if(u8MoveCursor==5)
		{
			u8MoveCursor=(u8MoveCursor-1-2)%6;
			LCD_voidMoveCourser(0,0,u8MoveCursor);
		}
		else
		{
			u8MoveCursor=(u8MoveCursor-2)%6;
			if(u8MoveCursor==0)
				LCD_voidMoveCourser(0,0,u8MoveCursor+1);
			else if(u8MoveCursor==2)
				LCD_voidMoveCourser(0,0,u8MoveCursor+2);
			else if(u8MoveCursor==4)
				LCD_voidMoveCourser(0,0,u8MoveCursor+3);
		}

}
void LCD_voidIncrement(void){

	switch(u8MoveCursor)
		{
		case 0:
			if(u8hour<9)
			{
			u8hour++;
			LCD_voidSendNumber(0,u8hour);
			LCD_voidMoveCourser(0,0,u8MoveCursor+1);
			}
			else if(u8hour>=9)
			{
				LCD_voidMoveCourser(0,0,u8MoveCursor);
				u8hour++;
				LCD_voidSendNumber(0,u8hour);
			}

			break;

		case 2:
			if(u8minute<9)
			{
			LCD_voidMoveCourser(0,0,u8MoveCursor+2);
			u8minute++;
			LCD_voidSendNumber(0,u8minute);

			}
			else if(u8minute>=9)
			{
				LCD_voidMoveCourser(0,0,u8MoveCursor+1);
				u8minute++;
				LCD_voidSendNumber(0,u8minute);
			}
			break;
		case 4:
			if(u8sec<9)
			{
				LCD_voidMoveCourser(0,0,u8MoveCursor+3);
				u8sec++;
				LCD_voidSendNumber(0,u8sec);

			}
			else if(u8sec>=9)
			{
				LCD_voidMoveCourser(0,0,u8MoveCursor+2);
				u8sec++;
				LCD_voidSendNumber(0,u8sec);

			}
			break;

		}


}
void LCD_voidDecrement(void){

	switch(u8MoveCursor)
		{
		case 0:
			if(u8hour!=0 && u8hour<=10)
			{
				u8hour--;
				LCD_voidMoveCourser(0,0,u8MoveCursor);
				LCD_voidSendChar(0,'0');

				LCD_voidMoveCourser(0,0,u8MoveCursor+1);

				LCD_voidSendNumber(0,u8hour);
			}
			else if(u8hour>10)
			{
				u8hour--;
				LCD_voidMoveCourser(0,0,u8MoveCursor);
				LCD_voidSendNumber(0,u8hour);
			}

			break;
		case 2:
			if(u8minute!=0 && u8minute<=10)
			{
				LCD_voidMoveCourser(0,0,u8MoveCursor+1);
				LCD_voidSendChar(0,'0');
				u8minute--;
				LCD_voidMoveCourser(0,0,u8MoveCursor+2);
				LCD_voidSendNumber(0,u8minute);

			}
			else if(u8minute>10)
			{
				LCD_voidMoveCourser(0,0,u8MoveCursor+1);
				u8minute--;
				LCD_voidSendNumber(0,u8minute);
			}
			break;
		case 4:
			if(u8sec!=0 && u8sec<=10)
			{
				LCD_voidMoveCourser(0,0,u8MoveCursor+2);
				LCD_voidSendChar(0,'0');
				u8sec--;
				LCD_voidMoveCourser(0,0,u8MoveCursor+3);
				LCD_voidSendNumber(0,u8sec);

			}
			else if(u8sec>10)
					{
						LCD_voidMoveCourser(0,0,u8MoveCursor+2);
						u8sec--;
						LCD_voidSendNumber(0,u8sec);
					}

			break;
		}

}
void LCD_voidTime(void){
	LCD_voidClrScr(0);
		LCD_voidSendString(0,"Time is set");
		_delay_ms(100);
		LCD_voidClrScr(0);
		LCD_voidSendString(0,"00:00:00");
		if(u8sec<=10)
		{
			LCD_voidMoveCourser(0,0,6);
			LCD_voidSendChar(0,'0');
			LCD_voidMoveCourser(0,0,7);
			LCD_voidSendChar(0,u8sec+48);
		}
		else if(u8sec>10)
		{
			LCD_voidMoveCourser(0,0,6);
			LCD_voidSendNumber(0,u8sec);
		}
		if(u8minute<=10)
			{
			LCD_voidMoveCourser(0,0,3);
			LCD_voidSendChar(0,'0');
			LCD_voidMoveCourser(0,0,4);
			LCD_voidSendChar(0,u8minute+48);
			}
		else if(u8minute>10)
		{
			LCD_voidMoveCourser(0,0,3);
			LCD_voidSendNumber(0,u8minute);
		}
		if(u8hour<=10)
		{
			LCD_voidMoveCourser(0,0,0);
			LCD_voidSendChar(0,'0');
			LCD_voidMoveCourser(0,0,1);
			LCD_voidSendChar(0,u8hour+48);
		}
		else if(u8hour>10)
		{
					LCD_voidMoveCourser(0,0,0);
					LCD_voidSendNumber(0,u8hour);
				}



		if(u8sec!=0)
		{
			u8sec=u8sec+1;
			while(u8sec!=0)
			{
				if(u8sec<=10)
				{
					LCD_voidMoveCourser(0,0,6);
					LCD_voidSendChar(0,'0');
					u8sec--;
					LCD_voidMoveCourser(0,0,7);
					LCD_voidSendChar(0,u8sec+48);
					_delay_ms(100);
				}

				else if(u8sec>10)
				{
					u8sec--;
					LCD_voidMoveCourser(0,0,6);
					LCD_voidSendNumber(0,u8sec);
					_delay_ms(100);

				}

				if(u8sec==0)
					break;
			}
		}

			if(u8minute!=0)
			{
				u8minute=u8minute+1;
				while(u8minute!=0)
				{
					if(u8minute<=10)
					{
						LCD_voidMoveCourser(0,0,3);
						LCD_voidSendChar(0,'0');
						u8minute--;
						LCD_voidMoveCourser(0,0,4);
						LCD_voidSendChar(0,u8minute+48);
						_delay_ms(1000);
						LCD_Second();
					}

					else if(u8minute>10)
					{
						u8minute--;
						LCD_voidMoveCourser(0,0,3);
						LCD_voidSendNumber(0,u8minute);
						_delay_ms(1000);
						LCD_Second();
					}

					if(u8minute==0)
						break;
				}

			}
			if(u8hour!=0)
			{
				u8hour=u8hour+1;
				while(u8hour!=0)
				{
					if(u8hour<=10)
					{
						LCD_voidMoveCourser(0,0,0);
						LCD_voidSendChar(0,'0');
						u8hour--;
						LCD_voidMoveCourser(0,0,1);
						LCD_voidSendChar(0,u8hour+48);
						_delay_ms(100);
						LCD_SecToMin();
					}

					else if(u8hour>10)
					{

						u8hour--;
						LCD_voidMoveCourser(0,0,0);
						LCD_voidSendNumber(0,u8hour);
						_delay_ms(100);
						LCD_SecToMin();

						}

						if(u8hour==0)
							break;
					}

				}


			LCD_voidClrScr(0);
			LCD_voidSendString(0,"It is the time");



}
void LCD_Second(void){
	u8sec=60;
		while(u8sec!=0)
		{
			if(u8minute==0)
					break;
			if(u8sec<=10)
			{
				LCD_voidMoveCourser(0,0,6);
				LCD_voidSendChar(0,'0');
				u8sec--;
				LCD_voidMoveCourser(0,0,7);
				LCD_voidSendChar(0,u8sec+48);
				_delay_ms(100);
			}

			else if(u8sec>10)
			{
				u8sec--;
				LCD_voidMoveCourser(0,0,6);
				LCD_voidSendNumber(0,u8sec);
				_delay_ms(100);

			}

		}



}
void LCD_Minutes(void){

	u8minute=60;
		while(u8minute!=0)
		{
			if(u8minute<=10)
			{
				LCD_voidMoveCourser(0,0,3);
				LCD_voidSendChar(0,'0');
				u8minute--;
				LCD_voidMoveCourser(0,0,4);
				LCD_voidSendChar(0,u8minute+48);
				_delay_ms(100);
			}

			else if(u8minute>10)
			{
				u8minute--;
				LCD_voidMoveCourser(0,0,3);
				LCD_voidSendNumber(0,u8minute);
				_delay_ms(100);

			}
			}
}
void LCD_SecToMin(void){

	u8sec=59;
		u8minute=59;
		LCD_voidMoveCourser(0,0,3);
		LCD_voidSendNumber(0,u8minute);

		while(u8minute!=0)
		{

			u8sec=60;
			while(u8sec!=0)
			{
			if(u8minute==0)
				break;
			if(u8sec<=10)
			{
				u8minute--;
				LCD_voidMoveCourser(0,0,4);
				LCD_voidSendChar(0,u8minute+48);
				LCD_voidMoveCourser(0,0,6);
				LCD_voidSendChar(0,'0');
				u8sec--;
				LCD_voidMoveCourser(0,0,7);
				LCD_voidSendChar(0,u8sec+48);
				_delay_ms(100);
			}

			else if(u8sec>10)
			{
				u8sec--;
				LCD_voidMoveCourser(0,0,6);
				LCD_voidSendNumber(0,u8sec);
				_delay_ms(100);

			}
			}
			if(u8minute<=10)
			{
				LCD_voidMoveCourser(0,0,3);
				LCD_voidSendChar(0,'0');
				u8minute--;
				LCD_voidMoveCourser(0,0,4);
				LCD_voidSendChar(0,u8minute+48);
				_delay_ms(100);
			}

			else if(u8minute>10)
			{
				u8minute--;
				LCD_voidMoveCourser(0,0,3);
				LCD_voidSendNumber(0,u8minute);
				_delay_ms(100);

			}
		}


}
