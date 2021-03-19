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
2. Electrical shema
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

For input I\'m using two HCSR-04 to recognise hand-swap and two microswitches.
For output I\'m using two SSRs to switch light on and off.

Pinout:

- D8 (output) is a common trigger for both HC-SR04.
- D7 (input) is a input from first HC-SR04 echo.
- D6 (input) is a input from second microswitch.
- D7 (input) is a input from second HC-SR04 echo.
- D2 (output) is a output for second SSR.
- D2 (output) is a output for first SSR.
- A0 (input) is a input from first microswitch.


<h2>
3. Important notes
</h2>

You <b><u>can\'t</u></b> check state of A0 on every loop iteration, because WiFi won\'t work (ESP8266 ~~bug~~ feature). It\'s best to do this every 20ms or so (you can experiment with lower or higher times if 20ms doesn\'t work).