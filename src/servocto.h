/*
 * Servocto v1.0
 */
/* 
 * Be aware that this library uses TIMER1 and only works on ATmega328P boards (for now)
 * therefore, you cannot use TIMER1, digital pin '9' and '10' for PWM generation.
 * Written by Daniel Sitrakiniaina Razafimaharavo
*/
#ifndef servocto_h
#define servocto_h
class servocto
{
  public:
    //initialize
    void begin(uint8_t num_servos);
    void end();
    //no voltage output
    bool noOutput(bool state);
    //inverts a signal
    bool invert(bool inverting);
    //write in degrees
    void writeAngle(uint8_t servo, uint8_t angle);
    //write in microseconds
    void writeMicros(uint8_t servo, int microseconds);
};
#endif
