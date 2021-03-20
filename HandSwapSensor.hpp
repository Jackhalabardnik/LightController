#pragma once

#include "LightControl.hpp"

class HandSwapSensor
{
public:

HandSwapSensor(int first_echo_pin, int second_echo_pin, int common_trigger_pin, LightControl *first_light, LightControl *second_light);

void update();

private:

struct Sensor 
{
    int echo_pin, last_measured_distance;
    unsigned long start_echo_time, last_swap_time;
    bool received_echo;
    LightControl *light; 
};

void prepare_pins();
void update_sensor(Sensor &sensor);

Sensor first_sensor, second_sensor;

int common_trigger_pin;
unsigned long last_check;

const double triggering_distance = 8.0;
const int minimal_swap_time = 500; 
const int minimal_trigger_time = 50;
};