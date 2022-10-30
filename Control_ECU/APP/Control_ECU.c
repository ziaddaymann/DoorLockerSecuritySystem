 /******************************************************************************
 *
 * [FILE NAME]: <Control_ECU.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <25/10/2022>
 *
 * [DESCRIPTION]: <Source file for CONTROL ECU>
 *
 *******************************************************************************/

#include "Control_ECU.h"



int counter,falsePasswords;

Timer1_Configtype timerConfig = {COMPARE,0,7813,Prescale_1024};
UART_ConfigType uartConfig = {Asynchronous,Even,one};

void start(void)
{
	SREG |= (1<<7);

	uint8 password[5] , confirmPassword[5] , passwordVerified , command;

	Buzzer_init();
	DcMotor_Init();
	Timer1_setCallBack(timerHandler);
	UART_init(&uartConfig);
	EEPROM_init();


	while(passwordVerified == 0)
	{
		receivePassword(password);

		receivePassword(confirmPassword);

		passwordVerified = verifyPassword(password, confirmPassword);
		UART_sendByte(passwordVerified);

		_delay_ms(UART_DELAY);
	}


	storePasswordeeprom(password);


	while(1)
	{
		uint8 passwordEEPROM[4];
		readPasswordeeprom(passwordEEPROM);
		command = UART_recieveByte();
		_delay_ms(UART_DELAY);

		if(command == '+')
		{
			receivePassword(password);

			if(verifyPassword(password, passwordEEPROM))
			{
				falsePasswords = 0;
				UART_sendByte(1);
				_delay_ms(UART_DELAY);
				openDoor();
			}

			else
			{
				UART_sendByte(0);
				_delay_ms(UART_DELAY);
				falsePasswords++;
				UART_sendByte(falsePasswords);
				_delay_ms(UART_DELAY);
				falsePassword();

			}
		}

		else if(command == '-')
		{
			receivePassword(password);


			passwordVerified = verifyPassword(password, passwordEEPROM);
			_delay_ms(UART_DELAY);
			UART_sendByte(passwordVerified);

			if(passwordVerified)
			{
				falsePasswords = 0;
				receivePassword(password);


				receivePassword(confirmPassword);

				passwordVerified = verifyPassword(password, confirmPassword);
				_delay_ms(UART_DELAY);
				UART_sendByte(passwordVerified);

				if(passwordVerified)
				{
					storePasswordeeprom(password);
				}

				else
				{
					// do nothing
				}

			}

			else
			{
				falsePasswords++;
				UART_sendByte(falsePasswords);
				_delay_ms(UART_DELAY);
				falsePassword();
			}
		}
	}
}


void receivePassword (uint8 password[])
{
	uint8 i;

	for (i=0 ; i<5 ; ++i)
	{
		password [i] = UART_recieveByte();
	}
	_delay_ms (UART_DELAY);
}



uint8 verifyPassword (uint8 password[] , uint8 confirmPassword[])
{
	uint8 i;

	for (i=0 ; i<5 ; ++i)
	{
		if (password[i] != confirmPassword[i])
		{
			return 0;
		}
	}
	return 1;
}




void openDoor (void)
{
	Timer1_init(&timerConfig);

	DcMotor_Rotate(CLOCKWISE);
	while (counter < 15);
	counter = 0;
	DcMotor_Rotate(STOP);


	while (counter < 3);
	counter = 0;
	DcMotor_Rotate(ANTICLOCKWISE);


	while (counter < 15);
	counter = 0;
	DcMotor_Rotate(STOP);
	Timer1_deInit();
}




void timerHandler(void)
{
	counter++;
}




void falsePassword (void)
{
	if (falsePasswords >= 3)
	{
		falsePasswords = 0;
		Timer1_init (&timerConfig);
		Buzzer_on();
		while (counter < 60);
		Buzzer_off();
		counter = 0;
		Timer1_deInit();
	}
}



void storePasswordeeprom (uint8 password[])
{
	uint8 i;
	for (i=0 ; i<5 ; ++i)
	{
	EEPROM_writeByte ((0X0090 + i) , (password[i]));
	_delay_ms(UART_DELAY);
	}
}



void readPasswordeeprom (uint8 password [])
{
	uint8 i;
	for (i=0 ; i<5 ; ++i)
	{
		EEPROM_readByte ((0x0090 + i) , (password + i));
		_delay_ms(100);
	}
}
