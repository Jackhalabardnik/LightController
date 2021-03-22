#include "WiFiSwitch.hpp"


WiFiSwitch::WiFiSwitch(LightControl* first_light, LightControl* second_light)
:server(HTTP_port)
{
    this->first_light = first_light;
    this->second_light = second_light;
}

void WiFiSwitch::initialise(const char* SSID, const char* pass)
{
    Serial.println("Start");

    delay(10000);

    Serial.println("End");

    try_to_connect(SSID, pass);

    server.begin(HTTP_port);
}

void WiFiSwitch::try_to_connect(const char* SSID, const char* pass)
{
    WiFi.begin(SSID,pass);

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

void WiFiSwitch::update()
{
    WiFiClient client = server.available();

    if (client) {

        Serial.println("new client");

        while (client.connected()) {

            if (client.available()) {

                strap_POST_header(client);

                char first_command = client.read();
                char second_command = client.read();

                send_header(client);
                
                Serial.write(first_command);
                Serial.write(second_command);

                bool skipped_first_command = is_command_skipped(first_command);
                bool skipped_second_command = is_command_skipped(second_command);

                bool result;

                if(skipped_first_command && skipped_second_command)
                {
                    result = true;
                }
                else if(skipped_first_command)
                {
                    result = try_to_parse_command(*second_light, second_command);
                }
                else if(skipped_second_command)
                {
                    result = try_to_parse_command(*first_light, first_command);
                }
                else
                {
                    result = try_to_parse_command(*first_light, first_command);
                    result |= try_to_parse_command(*second_light, second_command);
                }

                if(result)
                {
                    client.println("OK");
                }
                else
                {
                    client.println("ERR");
                }

                break;
            }
        }

        delay(1);

        client.stop();

        Serial.println("client disonnected");
    }
}

void WiFiSwitch::strap_POST_header(WiFiClient &client)
{
    boolean current_line_blank = false;
                
    char post_data = client.read();
    
    do
    {
        if (post_data == '\n') {

        current_line_blank = true;

        } else if (post_data != '\r') {

        current_line_blank = false;
        }
        
        post_data = client.read();
        
    } while(!(post_data == '\n' && current_line_blank));
}

void WiFiSwitch::send_header(WiFiClient &client)
{
    client.println("HTTP/1.1 200 OK");

    client.println("Content-Type: text/html");

    client.println("");

    Serial.println("\nConnected");
}

bool WiFiSwitch::is_command_skipped(char c)
{
    return c == '2';
}

bool WiFiSwitch::is_good_command(char c)
{
    return (c == '0' || c == '1');
}

bool WiFiSwitch::try_to_parse_command(LightControl &light, char command)
{
    if(is_good_command(command) == false)
    {
        return false;
    }

    int mode = int(command) - int('0');

    LightControl::LightState state = mode == 0 ? LightControl::LightState::OFF : LightControl::LightState::ON;

    return light.try_to_set_state(state);
}


