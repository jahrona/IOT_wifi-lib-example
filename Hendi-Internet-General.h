#ifndef Hendi-Internet-General_h
#define Hendi-Internet-General_h
#endif

#define EXAMPLE_NODE_CODE "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"

#ifndef TOPICS_AMOUNT
#define TOPICS_AMOUNT 0
#endif

//connectivity
#define CONNECT2LAN 0
#define CONNECT2WIFI 1

#define EXAMPLE_SSID "NOCOLA_DEV_ATAS"
#define EXAMPLE_PASS "NOCOLADEV2021"

unsigned int topic_n = 0;

bool wifi_mark, net_mark, connectivity_mark, free_mark, ping_mark, mqtt_mark;
bool abc_mark;

//profile
String local_wifi_ssid;
String local_wifi_pass;
String local_node_code;

//checker
unsigned long net_millis, mqtt_millis;
unsigned long check_net_interval = 10 * 1000;
unsigned long check_mqtt_interval = 10 * 1000;