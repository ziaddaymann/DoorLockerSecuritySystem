 /******************************************************************************
 *
 * [FILE NAME]: <Control_ECU.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <25/10/2022>
 *
 * [DESCRIPTION]: <Header file for CONTROL ECU>
 *
 *******************************************************************************/

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_



/*******************************************************************************
 *                                INCLUDES                                     *
 *******************************************************************************/
#include "../MCAL/UART/uart.h"
#include "../MCAL/I2C/i2c.h"
#include "../MCAL/TIMER/timer.h"
#include "../HAL/BUZZER/buzzer.h"
#include "../HAL/EXTERNAL_EEPROM/external_eeprom.h"
#include "../HAL/DC_MOTOR/dcMotor.h"
#include "avr/interrupt.h"
#include <util/delay.h>



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define KEYPAD_DELAY        600
#define UART_DELAY          130



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void start(void);
void receivePassword (uint8 password[]);
uint8 verifyPassword (uint8 password[] , uint8 confirmPassword[]);
void openDoor (void);
void timerHandler(void);
void falsePassword (void);
void storePasswordeeprom (uint8 password[]);
void readPasswordeeprom (uint8 password []);

#endif /* CONTROL_ECU_H_ */
