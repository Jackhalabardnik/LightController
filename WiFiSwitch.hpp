#include "LightControl.hpp"

class WiFiSwitch 
{
public:

    WiFiSwitch(LightControl* first_light, LightControl* second_light);

    void initialise(const char* SSID, const char* pass);

    void update();

 private:

    void try_to_connect(const char* SSID, const char* pass);

    void strap_POST_header(WiFiClient &client);

    void send_header(WiFiClient &client);

    bool is_good_command(int c);

    std::string change_lights(int first_command, int second_command);

    std::string get_light_status();

    bool try_to_parse_command(LightControl &light, int command);


    LightControl* first_light, *second_light;

    WiFiServer server;

    enum WiFiCommand 
    {
        TURN_OFF = int('0'),
        TURN_ON = int('1'),
        SWITCH = int('2'),
        SKIP = int('3'),
        STATUS = int('S')
    };

    const int HTTP_port = 80, disconnect_delay = 1;

};