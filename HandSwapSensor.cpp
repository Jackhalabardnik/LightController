#include "HandSwapSensor.hpp"

HandSwapSensor::HandSwapSensor(int first_echo_pin, int second_echo_pin, int common_trigger_pin, LightControl *first_light, LightControl *second_light)
{
    unsigned long time = millis();

    first_sensor = {first_echo_pin, 0, 0, time, false, first_light};
    second_sensor = {second_echo_pin, 0, 0, time, false, second_light};

    this->common_trigger_pin = common_trigger_pin;

    prepare_pins();

    last_check = time;
}

void HandSwapSensor::prepare_pins()
{
    pinMode(common_trigger_pin, OUTPUT);
    digitalWrite(common_trigger_pin,LOW);

    pinMode(first_sensor.echo_pin, INPUT);
    digitalWrite(first_sensor.echo_pin,LOW);

    pinMode(second_sensor.echo_pin, INPUT);
    digitalWrite(second_sensor.echo_pin,LOW);
}

void HandSwapSensor::update()
{
    if(millis() - last_check > minimal_trigger_time || millis() < last_check)
    {
        last_check = millis();
        first_sensor.received_echo = false;
        second_sensor.received_echo = false;

        digitalWrite(common_trigger_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(common_trigger_pin, LOW);
    }


    update_sensor(first_sensor);
    update_sensor(second_sensor);
}

void HandSwapSensor::update_sensor(Sensor &sensor)
{
    if(sensor.received_echo)
    {
        if(!digitalRead(sensor.echo_pin))
        {
            const double sensor_distance_const = 58.0;
            double distance = double(micros() - sensor.start_echo_time)/sensor_distance_const;

            if((millis() - sensor.last_swap_time > minimal_swap_time || millis() < sensor.last_swap_time) && distance < triggering_distance && sensor.last_measured_distance > triggering_distance)
            {
                sensor.light->switch_light();
                sensor.last_swap_time = millis();
            }

            sensor.last_measured_distance = distance;

            sensor.received_echo = false;
        }
    }
    else
    {
        if(digitalRead(sensor.echo_pin))
        {
            sensor.start_echo_time = micros();
            sensor.received_echo = true;
        }
    }
}