#include "LightControl.hpp"

LightControl::LightControl(int pin_number)
{
    pin = pin_number;
    pinMode(pin,OUTPUT);
    digitalWrite(pin,LOW);
    state = LightControl::OFF;
}

LightControl::LightState LightControl::get_state()
{
    return state;
}

bool LightControl::try_to_set_state(LightState desired_state)
{
    if(state == desired_state)
    {
        return false;
    }
    else
    {
        switch_light();
        return true;
    }    
}

void LightControl::switch_light()
{
    if(state == LightControl::ON)
    {
        digitalWrite(pin,LOW);
        state = LightControl::OFF;
    }
    else
    {
        digitalWrite(pin,HIGH);
        state = LightControl::ON;
    }
}