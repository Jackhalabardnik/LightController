#include "Password.hpp"
#include "Pins.hpp"
#include "LightSwitch.hpp"
#include "HandSwapSensor.hpp"
#include "WiFiSwitch.hpp"

LightControl first_light(first_SSR_pin);
LightControl second_light(second_SSR_pin);

LightSwitch first_switch(first_switch_pin, true);
LightSwitch second_switch(second_switch_pin, false);

HandSwapSensor hand_swap_sensor(SCL_pin, SDA_pin, second_sensor_power, sensor_enable_pin, &first_light, &second_light);

WiFiSwitch wifi_switch(&first_light, &second_light);

bool is_distance_sensor_working;

const int baud_rate = 115200;

void setup()
{
    Serial.begin(baud_rate);
    Serial.println("");

    wifi_switch.initialise(ssid, password);
    is_distance_sensor_working = hand_swap_sensor.init();
}

void loop()
{
    wifi_switch.update();
    first_switch.update(first_light);
    second_switch.update(second_light);
    if(is_distance_sensor_working)
    {
        hand_swap_sensor.update();
    } 
}