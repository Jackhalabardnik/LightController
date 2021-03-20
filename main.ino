#include "Password.hpp"
#include "Pins.hpp"
#include "LightSwitch.hpp"
#include "Distance_sensor_utils.hpp"


LightControl first_light(first_SSR_pin);
LightControl second_light(second_SSR_pin);

LightSwitch first_switch(first_switch_pin, true);
LightSwitch second_switch(second_switch_pin, false);

void try_to_connect()
{
    WiFi.begin(ssid,password);

    delay(5000);
    
    if(WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Connected!");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("No connection");
    }
    
}

void setup()
{
    Serial.begin(115200);

    Serial.println("");

    try_to_connect();
}

void loop()
{
    first_switch.update(first_light);
    second_switch.update(second_light);
}