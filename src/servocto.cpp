/*
 * Servocto v1.0
 */
/* 
 * Be aware that this library uses TIMER1 and only works on ATmega328P boards (for now)
 * therefore, you cannot use TIMER1, digital pin '9' and '10' for PWM generation.
 * Written by Daniel Sitrakiniaina Razafimaharavo
*/

#include "Arduino.h"
#include "servocto.h"
int val_servos[8];
int num_servos;
int acc;
void servocto::end()
{
	pinMode(9, INPUT);
	//Disable timer 01
	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1H = 0;
	TCNT1L = 0;
	ICR1 = 0;
	OCR1A = 0;
	OCR1B = 0;
	TIMSK1 = 0;
	sei();
}	
	
void servocto::begin(uint8_t num)
{
	if(num > 8) num = 8;
	if(num < 1) num = 1;
	num_servos = num;
  	for (int i = 0; i <= 7; i++)
  	{	
		val_servos[i] = 0xc8;
  	}
  	pinMode(9, OUTPUT);
  	//Initialize timer 01
  	cli();
  	TCCR1A = (1 << COM1A1) | (1 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (1 << WGM11) | (0 << WGM10);
  	TCCR1B = (0 << ICNC1) | (0 << ICES1) | (1 << WGM13) | (1 << WGM12) | (0 << CS12) | (1 << CS11) | (1 << CS10);
  	TCNT1H = 0x00;
  	TCNT1L = 0x00;
	ICR1 = 500;
	OCR1A = 50;
  	OCR1B = 0;
  	TIMSK1 = (0 << ICIE1) | (0 << OCIE1B) | (1 << OCIE1A) | (0 << TOIE1);
  	sei();
}

ISR(TIMER1_COMPA_vect)
{
	ICR1 = val_servos[OCR1B];
	OCR1B = 1 + OCR1B;
	if (OCR1B >= (num_servos + 1))
	{
		int acc = 0;
		for (int j = 0; j <= (num_servos - 1); j++)
		{
			acc = val_servos[j] + acc;
		}
		ICR1 = 4999 - acc;
		OCR1B = 0;
	}
}

void servocto::writeAngle(uint8_t servo, uint8_t angle)
{
	if (servo > 8) servo = 8;
	if (servo < 1) servo = 1;
	if (angle > 180) angle = 180;
	if (angle < 0) angle = 0;
	val_servos[servo - 1] = (angle * (250/180)) + 250;
}

void servocto::writeMicros(uint8_t servo, int microseconds)
{
	if (servo > 8) servo = 8;
  	if (servo < 1) servo = 1;
  	if(num_servos <= 6) //6 channels or less to get full extent
  	{
		if (microseconds > 2200) microseconds = 2200;
		if (microseconds < 500) microseconds = 500;
  	}
  	else
  	{
		if(servo > 1)
		{
			if (microseconds > 2000) microseconds = 2000;
			if (microseconds < 1000) microseconds = 1000;
		}
		else //only channel 1 is allowed to get a full extent
		{
			if (microseconds > 2200) microseconds = 2200;
			if (microseconds < 500) microseconds = 500;	
		}	
  	}
  	val_servos[servo - 1] = microseconds/4;
}

bool servocto::noOutput(bool state)
{
	if (state) OCR1A = ICR1;
	else OCR1A = 50;
	return state;
}

bool servocto::invert(bool invert)
{
	cli();
  	TCCR1A = (1 << COM1A1) | (invert << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (1 << WGM11) | (0 << WGM10);
  	sei();
}
	
