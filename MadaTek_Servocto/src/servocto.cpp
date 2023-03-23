#include "Arduino.h"
#include "servocto.h"

int val_servos[8];

void servocto::begin()
{
  for (int i = 0; i <= 8; i++) val_servos[i] = 0xc7;
  pinMode(9, OUTPUT);
  //Initialize timer 01
  cli();
  TCCR1A = (1 << COM1A1) | (1 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (1 << WGM11) | (0 << WGM10);
  TCCR1B = (0 << ICNC1) | (0 << ICES1) | (1 << WGM13) | (1 << WGM12) | (0 << CS12) | (1 << CS11) | (1 << CS10);
  TCNT1H = 0x00;
  TCNT1L = 0x00;
  ICR1 = 500;
  OCR1A = 128;
  OCR1B = 0;
  TIMSK1 = (0 << ICIE1) | (0 << OCIE1B) | (1 << OCIE1A) | (0 << TOIE1);
  sei();
}

ISR(TIMER1_COMPA_vect)
{
  ICR1 = val_servos[OCR1B];
  OCR1B = 1 + OCR1B;
  if (OCR1B >= 9)
  {
    int acc = 0;
    for (int i = 0; i <= 7; i++) acc = val_servos[i] + acc;
    ICR1 = 4999 - acc;
    digitalWrite(13, 1);
    digitalWrite(13, 0);
    OCR1B = 0;
  }
}

void servocto::writeAngle(uint8_t servo, uint8_t angle)
{
  if (servo > 8) servo = 8;
  if (angle > 180) angle = 180;
  if (angle < 0) angle = 0;
  val_servos[servo - 1] = map(angle, 0, 180, 0xc7, 0x1f3);
}

void servocto::writeMicros(uint8_t servo, int microseconds)
{
  if (servo > 8) servo = 8;
  if (servo < 1) servo = 1;
  if (microseconds > 2000) microseconds = 2000;
  if (microseconds < 1000) microseconds = 1000;
  val_servos[servo - 1] = map(microseconds, 1000, 2000, 0xc7, 0x1f3);
}

bool servocto::noOutput(bool state)
{
  if (state) OCR1A = ICR1;
  else OCR1A = 128;
  return state;
}
