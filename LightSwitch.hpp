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
    const int minimal_read_time = 30, minimal_switch_time = 200, pin_state_off = 0, pin_state_on = 1, analog_pin_voltage_level = 500 ;
};