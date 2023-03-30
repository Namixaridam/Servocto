# Servocto v1.0 How-To's
1. Initializing
Our library requires initialization for the modules to work properly, you can do it within the setup () function or anywhere else as long as the initialization runs once.
Specify how many channels you are going to use, minimum is **one (1)** and the maximum is **eight (8)**:
``` cpp
#define channels 8
#include <servocto.h>
servocto servos;
void setup ()
{
  servos.begin(channels); //initialization
}
```

2. How to write duty cycle
The duty cycle of a servomotor usually ranges from 1000µs to 2000µs.
If your application uses less than 6 channels, you are allowed to output from 500µs to 2200µs on all of them
but if you are using more than 6 channels, every channel's minima and maxima will be limited to 1000µs and 2000µs respectively except for channel 1
which makes it perfect for connecting throttle servo (gas engine) or an Electronic Speed Controller (ESC for short). 
![Servomotor timing diagram, from M.E.C. Technical Note](https://github.com/Namixaridam/Servocto/blob/main/MadaTek_Servocto/images/servo.png)
Writing to the servos can be done anywhere in the code after initialization:
``` cpp
servos.writeMicros(channel_number, duty_cycle);
```

3. Writing angle to the servos
Some people prefer to convert pulse to angle even though it is not very precise.
Analog servomotors have a range of 180 degrees, again the command can be used anywhere after initialization:  
``` cpp
servos.writeAngle(channel_number, angle);
```

4. Disabling all eight PWM outputs
**IMPORTANT NOTE**: Avoid using these methods when using generic RF TX/RX on a plane or a copter!

In some cases, you may want to disconnect your servos (thus not providing any feedback force to counter any unwanted movement) this is how it can be done:
   **Disabling the output**
``` cpp
servos.noOutput(true);
```

   **Re-enabling the PWM**
``` cpp
servos.noOutput(false);
```

  **Another alternative, although not recommended**
Disabling:
``` cpp
servos.end(); //disable, should run once
```
Re-enabling:
``` cpp
servos.begin(); //re-enable, should run once
```
