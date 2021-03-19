#include <ESP8266WiFi.h>
#include "password.hpp"

void try_to_connect()
{
    WiFi.begin(ssid,password);

    delay(15000);
    
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

}