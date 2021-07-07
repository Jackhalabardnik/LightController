#pragma once

#include "LightControl.hpp"
#include "Adafruit_VL53L0X.h"

class HandSwapSensor
{
    public:

    HandSwapSensor(int _SCL_pin, int _SDA_pin, int _second_sensor_power, int _sensor_enable_pin, LightControl *first_light, LightControl *second_light);

    void update();

    bool init();

    private:

    void prepare_pins();

    void show_init_output(int blinks);

    enum InitResult
    {
        SUCCESS = 1,
        FIRST_SENSOR_FAILURE = 2,
        SECOND_SENSOR_FAILURE = 3
    };

    int SCL_pin, SDA_pin, second_sensor_power, sensor_enable_pin;
    long first_sensor_last_distance, second_sensor_last_distance, last_check_time;

    const double max_triggering_distance_mm = 100.0, min_triggering_distance_mm = 1.0;
    const int minimal_measure_time = 25, first_lox_adress = 0x30, second_lox_adress = 0x31, debug_led_pin = 2;

    Adafruit_VL53L0X first_lox, second_lox;

    LightControl *first_light, *second_light;
};