/*
    Developed by Hendi Hart at 2023
    define minimum one of below in main ino file
    WIFI_USE
    LAN_USE
    GSM_USE
*/

#ifndef Hendi-Internet_h
#define Hendi-Internet_h
#endif

#include "Arduino.h"
#include <NTPClient.h>
#include <PubSubClient.h>
#include <WebServer.h>
#include "Hendi-Internet-General.h"
#include "Hendi-MQTT.h"
#include "Hendi-Internet-Function.h"

// void callback(char* topic, byte* payload, unsigned int length);
// bool connectMqtt(PubSubClient* the_pointer, String the_node_code);

#ifdef WIFI_USE
  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <WiFiUdp.h>
  #include "Hendi-Wifi.h"

  // extern WiFiClient wifi_Client;
  // extern WiFiUDP ntp_UDP;
  // extern NTPClient time_Client;
  // extern PubSubClient wifi_MQTT;

#endif

