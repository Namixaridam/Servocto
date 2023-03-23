
int angle = 0;
#include "servocto.h"
void setup()
{
  delay(10);
  pinMode(13,OUTPUT);
  servos.begin();
}


void loop()
{ // put your main code here, to run repeatedly:
  for (int i = 1; i <= 8; i++)
  {
    angle = random(0, 180);
    servos.writeAngle(i, angle);
    delay(50);
  }
}
