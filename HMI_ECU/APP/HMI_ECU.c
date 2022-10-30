 /******************************************************************************
 *
 * [FILE NAME]: <HMI_ECU.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <26/10/2022>
 *
 * [DESCRIPTION]: <Source file for HMI ECU>
 *
 *******************************************************************************/

#include "HMI_ECU.h"


int counter;

Timer1_Configtype timerConfig = {COMPARE,0,7813,Prescale_1024};
UART_ConfigType uartConfig = {Asynchronous,Even,one};

void start(void){
	SREG |= (1<<7);

	LCD_init();
	UART_init(&uartConfig);



	uint8 password[5] , confirmPassword[5] , passwordVerified , command ;

	Timer1_setCallBack(timerHandler);

	while(passwordVerified == 0)
	{
		LCD_clearScreen();
		LCD_displayString("Plz enter pass");


		enterPassword(password);
		_delay_ms(UART_DELAY);
		sendPassword(password);

		LCD_clearScreen();
		LCD_displayString("Confirm Pass");
		enterPassword( confirmPassword );
		_delay_ms(UART_DELAY);
		sendPassword( confirmPassword );
		_delay_ms(UART_DELAY);

		passwordVerified = UART_recieveByte();
		_delay_ms(UART_DELAY);

		if(passwordVerified)
		{
			LCD_clearScreen();
			LCD_displayString("Right Password");
		}

		else
		{
			LCD_clearScreen();
			LCD_displayString("Wrong Password");
		}

		_delay_ms(3000);

	}

	while(1)
	{
		optionsDisplay();
		command = KEYPAD_getPressedKey();
		_delay_ms(KEYPAD_DELAY);
		UART_sendByte(command);
		_delay_ms(UART_DELAY);
		if(command == '+')
		{
			LCD_clearScreen();
			LCD_displayString("Plz enter pass");
			enterPassword(password);
			_delay_ms(UART_DELAY);
			sendPassword(password);
			passwordVerified = 0;
			passwordVerified = UART_recieveByte();
			if(passwordVerified)
			{
				openDoor();
			}

			else
			{
				uint8 falsePasswordCounter = UART_recieveByte();
				if(falsePasswordCounter >=3)
				{
					securityAlarm();
				}

				else
				{
					LCD_clearScreen();
					LCD_displayString("Wrong Password");
					_delay_ms(2500);
				}

			}

		}

		else if(command == '-')
		{
			LCD_clearScreen();
			LCD_displayString("Enter old pass");


			enterPassword(password);
			_delay_ms(UART_DELAY);
			sendPassword(password);

			passwordVerified = 0;
			passwordVerified = UART_recieveByte();


			if(passwordVerified)
			{
				LCD_clearScreen();
				LCD_displayString("Enter New pass");

				enterPassword(password);
				_delay_ms(UART_DELAY);
				sendPassword(password);

				LCD_clearScreen();
				LCD_displayString("Confirm New pass");

				enterPassword( confirmPassword );
				_delay_ms(UART_DELAY);
				sendPassword( confirmPassword );
				_delay_ms(UART_DELAY);

				passwordVerified = 0;
				passwordVerified = UART_recieveByte();

				if(passwordVerified)
				{
					LCD_clearScreen();
					LCD_displayString("Password Changed");
					_delay_ms(3000);
				}

				else
				{
					LCD_clearScreen();
					LCD_displayString("Wrong Password");
					_delay_ms(2500);
				}
			}

			else
			{
				uint8 falsePasswordCounter = UART_recieveByte();
				if(falsePasswordCounter >=3)
				{
					securityAlarm();
				}

				else
				{
					LCD_clearScreen();
					LCD_displayString("Wrong Password");
					_delay_ms(2500);
				}
			}
		}
	}
}

void enterPassword (uint8 password[])
{
	uint8 i;
	LCD_moveCursor(1, 5);

	for (i=0 ; i<6 ;++i)
	{
		while ((KEYPAD_getPressedKey() != 13) && (i == 5));

		password[i] = KEYPAD_getPressedKey();
		_delay_ms (KEYPAD_DELAY);
		LCD_displayCharacter('*');
	}

	_delay_ms (KEYPAD_DELAY);
}

void sendPassword (uint8 password[])
{
	uint8 i;

	for (i=0 ; i<5 ; ++i)
	{
		UART_sendByte (password[i]);
	}
	_delay_ms (UART_DELAY);
}

void optionsDisplay (void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "- :Change PW");
	LCD_displayStringRowColumn(1, 0, "+ :Open Door");
}

void openDoor (void)
{
	Timer1_init(&timerConfig);

	LCD_clearScreen();
	LCD_displayString("Opening Door....");

	while (counter < 15);
	counter = 0;

	LCD_clearScreen();
	LCD_displayString("Door Opened");

	while (counter < 3);
	counter = 0;

	LCD_clearScreen();
	LCD_displayString("Closing Door....");

	while (counter < 15);
	counter = 0;

	Timer1_deInit();
}


void securityAlarm (void)
{
	Timer1_init(&timerConfig);

	LCD_clearScreen();
	LCD_displayString("Security Alarm....");

	while (counter < 60);
	counter = 0;

	Timer1_deInit();
}


void timerHandler (void)
{
	counter++;
}

