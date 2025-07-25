# Servocto v1.0 How-To's<br>

## Initializing<br>
Our library requires initialization for the modules to work properly, you can do it within the setup () function or anywhere else as long as the initialization runs once.
Specify how many channels you are going to use, minimum is **one (1)** and the maximum is **eight (8)**:<br>
``` cpp
#define channels 8
#include <servocto.h>
servocto servos;
void setup ()
{
  servos.begin(channels); //initialization
}
```

## How to write duty cycle<br>
The duty cycle of a servomotor usually ranges from 1000µs to 2000µs.<br>
If your application uses less than 6 channels, you are allowed to output from 500µs to 2200µs (cannot go beyond 2200µs due to mechanical limit on servos) on all of them but if you are using more than 6 channels, every channel's minima and maxima will be limited to 1000µs and 2000µs respectively except for channel 1 which makes it perfect for connecting throttle servo (gas engine) or an Electronic Speed Controller (ESC for short). <br>
![Servomotor timing diagram, from M.E.C. Technical Note](https://github.com/Namixaridam/Servocto/blob/main/images/servo.png)<br>
Writing to the servos can be done anywhere in the code after initialization:
``` cpp
servos.writeMicros(channel_number, duty_cycle);
```

## Writing angle to the servos<br>
Some people prefer to convert pulse to angle even though it is not very precise.<br>
Analog servomotors have a range of 180 degrees, again the command can be used anywhere after initialization:<br>  
``` cpp
servos.writeAngle(channel_number, angle);
```
## Inverting the output signal
Depending on your configuration, you may want to invert the polarity of the signal (ie not the servocto hardware), inversion is true by default because it eases the decoding and transmission.   
It can be easily done by adding:
``` cpp
//inverting is true by default
servos.invert(false); 
```

## Disabling all eight PWM outputs<br> 
In some cases, you may want to disconnect your servos (ie. The servos aren't energized and their shafts can rotate freely). Disabling the PWM outputs to the servos or ESCs can help you to save some power since the motors are not powered, this is how it can be done:<br>
   **Disabling the output**<br>
``` cpp
servos.noOutput(true);
```

   **Re-enabling the PWM**<br>
``` cpp
servos.noOutput(false);
```

  **Another alternative, although not recommended**<br>
Disabling:<br>
``` cpp
servos.end(); //disable, should run once
```
Re-enabling:<br>
``` cpp
servos.begin(channels); //re-enable, should run once
```
**IMPORTANT NOTE**: Avoid using these methods when using generic OOK RX ISM modules on a plane or a copter!<br>
 
 
# Decoding the signals<br> 
The servocto decoder, featuring an input glitch filtering for RF OOK receiving operations:
![Decoder for Servocto](https://github.com/Namixaridam/Servocto/blob/main/images/nanoRF.jpg)<br>
