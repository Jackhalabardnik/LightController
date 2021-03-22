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
    int pin_state = 0;

    if (millis() - last_read_time > minimal_read_time || millis() < last_read_time)
    {
        if(is_in_analog_mode)
        {
            pin_state = analogRead(pin) > 500 ? 1 : 0;
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
    
    if(pin_state == 1 && last_state == 0 && (millis() - last_switch_time > 200 || millis() < last_switch_time))
    {
        last_switch_time = millis();
        light.switch_light();
    }

    last_state = pin_state;
}