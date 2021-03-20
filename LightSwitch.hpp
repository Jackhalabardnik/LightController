#pragma once
#include "LightControl.hpp"

class LightSwitch {
public:

    LightSwitch(int pin_number, bool is_analog_mode);

    void update(LightControl &light);

private:
    
    int pin;
    bool last_state, is_in_analog_mode;
    unsigned long last_switch_time;
    unsigned long last_read_time;
    const int minimal_read_time = 20;
};