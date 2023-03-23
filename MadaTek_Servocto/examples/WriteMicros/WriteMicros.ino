
int duty = 0;
#include <servocto.h>
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
    duty = random(1000, 2000);
    servos.writeMicros(i, duty);
    delay(50);
  }
}
