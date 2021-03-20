#pragma once
#include <ESP8266WiFi.h>

class LightControl 
{
public:

    enum LightState { ON,  OFF };

    LightControl(int pin_number);

    LightState get_state();

    bool try_to_set_state(LightState desired_state);

    void switch_light();

private:
    LightState state;
    int pin;
};