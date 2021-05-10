/*
COMP2215 COMP SYS 2 PROJECT (TASK 7)
by Jakub Dylag


MIT licence:
Copyright 2021 Jakub Dylag

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define MIN_STEP    2    /* > 0 */
#define MAX_STEP  255

void init(void);

int8_t dutyCycle = 0;
int8_t enc_delta(void);
volatile int8_t delta;



int main(void)
{	
	int16_t res;
	int16_t old;

	init();
	
	dutyCycle = 20;
	OCR0A = dutyCycle;
	
	sei();

	while(1)
	{
		_delay_ms(5);
		old = dutyCycle;
		res = dutyCycle + enc_delta();
		if (old != res)
		{
			if (res > MAX_STEP) {
				dutyCycle = MAX_STEP;
			} else if (res < MIN_STEP) {
				dutyCycle = MIN_STEP;
			} else {
				dutyCycle = res;
			}
			OCR0A = dutyCycle;
		}
	}
}


void init(void) {
	//DDRD = (1 << PORTD6);
	DDRB  |=  _BV(PB7);   /* inbuilt LED pin out */
	//DDRD  |=  _BV(PD0);   /* IO LED pin out */

	//Fast PWM mode, Clear OC0A on Compare Match, set OC0A at TOP
	TCCR0A = _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
	//throw interrupt on overflow
	TIMSK0 = _BV(TOIE0);
	
	//TCCR0B = (1 << CS00) | (1 << CS02);
	TCCR0B = _BV(CS01) | _BV(CS00);   /* Prescaler: F_CPU / 64, DS Table 14-8 */
	

	TCCR1A = _BV(WGM11);  /* CTC Mode, DS Table 14-7 */
	TCCR1B = _BV(CS11)
		   | _BV(CS10);   /* Prescaler: F_CPU / 64, DS Table 14-8 */
	OCR1A = (uint8_t)(F_CPU / (64.0 * 1000) - 1);
	TIMSK1 |= _BV(OCIE1A);  /* Enable timer interrupt, DS 14.8.6  */



}


//interrupt for timer overflow
/*ISR(TIMER0_OVF_vect)
{
	OCR0A = dutyCycle;
}*/

ISR( TIMER1_COMPA_vect ) {
    static int8_t last;
    int8_t new, diff;
    uint8_t wheel;


     /*
        Scan rotary encoder
        ===================
        This is adapted from Peter Dannegger's code available at:
        http://www.mikrocontroller.net/articles/Drehgeber
     */

     wheel = PINE;
     new = 0;
     if( wheel  & _BV(PE4) ) new = 3;
     if( wheel  & _BV(PE5) )
     new ^= 1;                  /* convert gray to binary */
     diff = last - new;         /* difference last - new  */
     if( diff & 1 ){            /* bit 0 = value (1) */
         last = new;                /* store new as next last  */
         delta += (diff & 2) - 1;   /* bit 1 = direction (+/-) */
     }

}


/* read two step encoder */
int8_t enc_delta() {
	int8_t val;

	cli();
	val = delta;
	delta &= 1;
	sei();

	return val >> 1;
}

