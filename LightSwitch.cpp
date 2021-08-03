#include "LightSwitch.hpp"

LightSwitch::LightSwitch(int pin_number, bool is_analog_mode)
{
    pin = pin_number;
    is_in_analog_mode = is_analog_mode;
    last_switch_time = millis();
    last_read_time = millis();

    pinMode(pin,INPUT);
    if(!is_in_analog_mode)
    {
        digitalWrite(pin,LOW);
    }
}

void LightSwitch::update(LightControl &light)
{
    int pin_state = pin_state_off;

    if (millis() - last_read_time > minimal_read_time || millis() < last_read_time)
    {
        if(is_in_analog_mode)
        {
            pin_state = analogRead(pin) > analog_pin_voltage_level ? pin_state_on : pin_state_off;
        }
        else
        {
            pin_state = digitalRead(pin);
        }
        last_read_time = millis();
    }
    else
    {
        pin_state = last_state;
    }
    
    if(pin_state == pin_state_on && last_state == pin_state_off && (millis() - last_switch_time > minimal_switch_time || millis() < last_switch_time))
    {
        last_switch_time = millis();
        light.switch_light();
    }

    last_state = pin_state;
}