#include "HandSwapSensor.hpp"

HandSwapSensor::HandSwapSensor(int _SCL_pin, int _SDA_pin, int _second_sensor_power, int _sensor_enable_pin, LightControl *_first_light, LightControl *_second_light)
{
    unsigned long time = millis();

    SCL_pin = _SCL_pin;
    SDA_pin = _SDA_pin;
    second_sensor_power = _second_sensor_power;

    first_light = _first_light;
    second_light = _second_light;

    sensor_enable_pin = _sensor_enable_pin;

    prepare_pins();

    last_check_time = time;
}

void HandSwapSensor::prepare_pins()
{
    pinMode(SCL_pin, OUTPUT);
    digitalWrite(SCL,LOW);

    pinMode(SDA_pin, OUTPUT);
    digitalWrite(SDA,LOW);

    pinMode(second_sensor_power, OUTPUT);
    digitalWrite(second_sensor_power,LOW);

    pinMode(sensor_enable_pin, INPUT);
    digitalWrite(sensor_enable_pin,LOW);
}

void HandSwapSensor::init()
{
    Wire.pins(SDA_pin,SCL_pin);

    if (!first_lox.begin(first_lox_adress, false, &Wire))
    {
        Serial.println(F("Failed to boot first distance sensor"));
        pinMode(2, OUTPUT);
        digitalWrite(2,LOW);
        while(1);
    }

    digitalWrite(second_sensor_power, HIGH);
    delay(10);

    if (!second_lox.begin(second_lox_adress, false, &Wire))
    {
        Serial.println(F("Failed to boot second distance sensor"));
        pinMode(2, OUTPUT);
        digitalWrite(2,LOW);
        while(1);
    }
}
void HandSwapSensor::update()
{
    if(millis() - last_check_time > minimal_measure_time || millis() - last_check_time < 0)
    {
        if(digitalRead(sensor_enable_pin))
        {
            VL53L0X_RangingMeasurementData_t first_measure;
            VL53L0X_RangingMeasurementData_t second_measure;

            first_lox.rangingTest(&first_measure, false);
            second_lox.rangingTest(&second_measure, false);

            if (first_measure.RangeStatus == 0)
            {
                int distance = first_measure.RangeMilliMeter;
                if(distance < max_triggering_distance_mm && distance > min_triggering_distance_mm && first_sensor_last_distance > max_triggering_distance_mm)
                {
                    first_light->switch_light();
                }
                first_sensor_last_distance = distance;
            }
            else
            {
                first_sensor_last_distance = max_triggering_distance_mm + 10;
            }

            if (second_measure.RangeStatus == 0)
            {
                int distance = second_measure.RangeMilliMeter;
                if(distance < max_triggering_distance_mm && distance > min_triggering_distance_mm && second_sensor_last_distance > max_triggering_distance_mm)
                {
                    second_light->switch_light();
                }
                second_sensor_last_distance = distance;
            }
            else
            {
                second_sensor_last_distance = 110;
            }
            
        }

        last_check_time = millis();
    }
}
