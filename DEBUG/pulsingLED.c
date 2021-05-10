/*
COMP2215 COMP SYS 2 PROJECT (TASK 7)
by Jakub Dylag
*/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int8_t dutyCycle = 0;

int main(void)
{	
	//DDRD = (1 << PORTD6);
	DDRB  |=  _BV(PB7);   /* inbuilt LED pin out */
	//DDRD  |=  _BV(PD0);   /* IO LED pin out */

	//Fast PWM mode, Clear OC0A on Compare Match, set OC0A at TOP
	TCCR0A = _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
	//throw interrupt on overflow
	TIMSK0 = _BV(TOIE0);
	
	OCR0A = 10;

	//TCCR0B = (1 << CS00) | (1 << CS02);
	TCCR0B = _BV(CS01) | _BV(CS00);   /* Prescaler: F_CPU / 64, DS Table 14-8 */

	sei();
	
    while(1)
    {
        //TODO:: Please write your application code
		//_delay_ms(100);
		
		dutyCycle += 1;
		
		if(dutyCycle > 255)
		{
			dutyCycle = 0;
		}

		OCR0A = dutyCycle;						
    }
}

//interrupt for timer overflow
ISR(TIMER0_OVF_vect)
{
	OCR0A = dutyCycle;
}