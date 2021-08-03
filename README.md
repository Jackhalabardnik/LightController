<h1>
Code for esp8266 light controller
</h1>


------------

**Disclaimer**

This is just a prototype and I make no guarantee that it will work or be safe.
If you attempt to build it, you do so at your own risk.

------------

Table of contents:
1. Quick run instruction
2. Electrical schema
3. Important notes

<h2>
1. Quick run instruction
</h2>

If you want to use my code, you have to create file \"password.hpp\", and then put there following code:
`#include <string>`
`const char* ssid = "AAA";`
`const char* password = "BBB";`

Of course you will need to change \"AAA\" to your WiFi SSID and \"BBB\" to your WiFi password.

<h2>
2. Electrical shema
</h2>

For input I\'m using two VL53L0X to recognise hand-swap and two microswitches.
For output I\'m using two SSRs to switch light on and off.

Pinout:

- D8 (output) is a second sensor VCC<sup>1</sup>.
- D7 (input) is an I2C SDA.
- D6 (input) is a input from second microswitch.
- D5 (input) is an I2C SCL.
- D2 (output) is a output for second SSR.
- D1 (output) is a output for first SSR.
- D0 (input) is a input from manual switch (turn off/on distance sensors)
- A0 (input) is a input from first microswitch.

<sup>1</sup> I know that I should use another pin to turn off/on I2C sensor, but previous version used only 8 outputs on a board to operate distance sensors and because sensor current is about 10mA I decided to use this trick and do less soldering.  

<h2>
3. Important notes
</h2>

You <b><u>can\'t</u></b> check state of A0 on every loop iteration, because WiFi won\'t work (ESP8266 ~~bug~~ feature). It\'s best to do this every 20ms or so (you can experiment with lower or higher times if 20ms doesn\'t work).