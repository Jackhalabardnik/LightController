#include "WiFiSwitch.hpp"


WiFiSwitch::WiFiSwitch(LightControl* first_light, LightControl* second_light)
:server(HTTP_port)
{
    this->first_light = first_light;
    this->second_light = second_light;
}

void WiFiSwitch::initialise(const char* SSID, const char* pass)
{
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

        while (client.connected()) {

            if (client.available()) {

                strap_POST_header(client);

                int first_command = int(client.read());
                int second_command = int(client.read());

                send_header(client);

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

        delay(disconnect_delay);

        client.stop();
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
}

bool WiFiSwitch::is_command_skipped(int c)
{
    return c == WiFiCommand::SKIP;
}

bool WiFiSwitch::is_good_command(int c)
{
    return (c == WiFiCommand::TURN_OFF || c == WiFiCommand::TURN_ON || c == WiFiCommand::SWITCH);
}

bool WiFiSwitch::try_to_parse_command(LightControl &light, int command)
{
    if(is_good_command(command) == false)
    {
        return false;
    }

    if(command == WiFiCommand::SWITCH)
    {
        light.switch_light();
        return true;
    }
    
    if(command == WiFiCommand::TURN_ON)
    {
        return light.try_to_set_state(LightControl::LightState::ON);
    }
    
    return light.try_to_set_state(LightControl::LightState::OFF);
}


