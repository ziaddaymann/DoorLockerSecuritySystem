 /******************************************************************************
 *
 * [FILE NAME]: <HMI_ECU.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <26/10/2022>
 *
 * [DESCRIPTION]: <Header file for HMI ECU>
 *
 *******************************************************************************/

#ifndef HMI_ECU_H_
#define HMI_ECU_H_


/*******************************************************************************
 *                                INCLUDES                                     *
 *******************************************************************************/
#include "../HAL/LCD/lcd.h"
#include "../HAL/KEYPAD/keypad.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/TIMER/timer.h"
#include "util/delay.h"
#include "avr/interrupt.h"




/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define KEYPAD_DELAY        500
#define UART_DELAY          50



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void start(void);
void enterPassword (uint8 password[] );
void sendPassword (uint8 password[] );
void optionsDisplay (void);
void openDoor (void);
void securityAlarm (void);
void timerHandler (void);

#endif /* HMI_ECU_H_ */
