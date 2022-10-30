 /******************************************************************************
 *
 * [FILE NAME]: <timer.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <25/10/2022>
 *
 * [DESCRIPTION]: <Source file for TIMER1 Driver>
 *
 *******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "../../LIB/common_macros.h"

/*******************************************************************************
 *                    Global Private Function                                  *
 *******************************************************************************/
void (*g_Timer1CallBackPtr)(void) = NULL_PTR;



/*******************************************************************************
 *                                ISR                                          *
 *******************************************************************************/
/* Timer1 OVERFLOW mode */
ISR(TIMER1_OVF_vect)
{
	if (*g_Timer1CallBackPtr != NULL_PTR)
	{
		(*g_Timer1CallBackPtr)();
	}
}

/* Timer1 COMPARE mode */
ISR(TIMER1_COMPA_vect)
{
	if (*g_Timer1CallBackPtr != NULL_PTR)
	{
		(*g_Timer1CallBackPtr)();
	}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description: A function that initialize a timer1 with dynamic configurations.
 *
 */
void Timer1_init(const Timer1_Configtype * Config_Ptr)
{
        TCCR1A =0;
		SET_BIT(TCCR1A,FOC1A); /* for non-PWM mode */
		SET_BIT(TCCR1A,FOC1B);
		TCCR1B = Config_Ptr->prescale;
		TCNT1 = Config_Ptr->initialvalue;

		if( (Config_Ptr -> mode) == NORMAL )
		{
			/* Enable interrupts for overflow mode */
			SET_BIT(TIMSK,TOIE1);
			/* Enable overflow flag */
			SET_BIT(TIFR,TOV1);
		}
		else if ( (Config_Ptr -> mode) == COMPARE )
		{
			SET_BIT(TCCR1B,WGM12);
			OCR1A = Config_Ptr -> comparevalue;
			SET_BIT(TIMSK,OCIE1A); /* enable interrupts for CTC mode */
			SET_BIT(TIFR,OCF1A); /* enable CTC flag */
		}
}


/*
 * Description: A function that Deinitialize a timer1 with dynamic configurations.
 *
 */
void Timer1_deInit(void)
{
	TCCR1A =0;
	TCCR1B = 0; /* disable clock */
	TCNT1 = 0;
	CLEAR_BIT(TIMSK, TOIE1); /* disable interrupts for overflow mode */
	OCR1A = 0;  /* clear compare value for CTC mode */
	CLEAR_BIT(TIMSK, OCIE1A); /* disable interrupts for CTC mode */
	g_Timer1CallBackPtr = NULL_PTR;
}



/*
 * Description: A function that Call Back A Function.
 *
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_Timer1CallBackPtr = a_ptr;
}


/*
 * Description: A function that set a new value.
 *
 */
void Timer1_setValue (uint8 newValue)
{
	TCNT1 = newValue;
}

/*
 * Description: A function that clear the value.
 *
 */
void Timer1_clearValue(void)
{
	TCNT1 = 0;
}
