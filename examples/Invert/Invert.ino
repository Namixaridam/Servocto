/*
 * Some PPM decoders use positive PPM signals, the others expect a negative going signal
 * the invert() function lets you change the output signal
 * 
 * 
 * Written by Daniel Sitrakiniaina Razafimaharavo
*/

#define channels 8 //How many channels you want to transmit, min = 1 and max = 8
int duty = 0;
bool inversion = 0;
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
  //Inverts PPM signal
  servos.invert(inversion);
  inversion != inversion;
  delay(5000);
}