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

    bool is_good_command(char c);

    bool is_command_skipped(char c);

    bool try_to_parse_command(LightControl &light, char command);


    LightControl* first_light, *second_light;

    WiFiServer server;

    const int HTTP_port = 80;

};