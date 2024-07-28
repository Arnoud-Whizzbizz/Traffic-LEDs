Traffic-LEDs - Whizzbizz.com - Arnoud - July 2024

Traffic LEDs for two directions. Sequences are configurable in an array of structs.

The cycle in which the colored lights alternate or burn at the same time differs from country to country.
In the Netherlands, only one light of the tri-color traffic is on at a time. Here in the Netherlands, the
red light jumps directly to green. In other countries, for example Germany, Hungary, Great Britain, Austria, 
Switzerland, Poland, Lithuania, Norway, Russia and Sweden, before the red light turns green, the orange light
is lit together with the red light to indicate that the green light will be lit soon.

The Sketch was written for Arduino. Mega Pro Mini board was used, but should also work with Uno and other types.
This Sketch also reads two inputs (touch sensors) at inputs D12 and D13
Sensor 1 off/false shows the 'Dutch traffic lights sequence'
Sensor 1 on/true switches to the 'German traffic lights sequence'
When sensor 2 is on/true it overrules and only the two yellow lights will blink

In /Gerbers PCBs/ you'll find the Gerbers of the tiny PCB to mount your own additional series resistors and the optional raiser PCB.

In /3D files/ you'll find the STL files to print the small casing to be used with the fischertechnik construction system. 
I've also included the STL file to print the Arduino Mega Pro Mini casing that can be used with the fischertechnik construction system. 

For a more detailed description, see the project page at https://www.whizzbizz.com/en/mini-traffic-lights
