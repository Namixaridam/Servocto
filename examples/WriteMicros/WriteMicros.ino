/*
 * Servocto v1.0
 */
/* 
 * Be aware that this library uses TIMER1 and only works on ATmega328P boards (for now)
 * therefore, you cannot use TIMER1, digital pin '9' and '10' for PWM generation.
 * Written by Daniel Sitrakiniaina Razafimaharavo
*/

#define channels 8 //How many channels you want to transmit, min = 1 and max = 8
int duty = 0;

#include <servocto.h>
servocto servos;
void setup()
{
//initialize the servos
  servos.begin(channels);
}


void loop()
{
	// put your main code here, to run repeatedly:
//writes a random pulse width to the servos
  for (int i = 1; i <= channels; i++)
  {
    duty = random(1000, 2000);
    servos.writeMicros(i, duty);
    delay(2000 / channels);
  }
}
