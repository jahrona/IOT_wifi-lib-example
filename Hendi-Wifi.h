#ifndef Hendi-Wifi_h
#define Hendi-Wifi_h
#endif

#include "Arduino.h"
#include <NTPClient.h>
#include <PubSubClient.h>


#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

WiFiClient wifi_Client;
WiFiUDP ntp_UDP;
NTPClient time_Client(ntp_UDP, "id.pool.ntp.org");
PubSubClient wifi_MQTT(wifi_Client);

unsigned long getTimeWifi() {
    time_Client.forceUpdate();
    unsigned long epoch_time = time_Client.getEpochTime();
    Serial.println(epoch_time);
    return epoch_time;
}

bool connectWifi(String wifi_ssid = local_wifi_ssid, String wifi_pass = local_wifi_pass) {
  WiFi.disconnect();
  delay(3000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid.c_str(), wifi_pass.c_str());
  Serial.print("Connect to : ");
  Serial.println(local_wifi_ssid);
  delay(500);
  Serial.println("Try connect wifi");
  delay(200);
  int try_mark = 0;
  while ((WiFi.status() != WL_CONNECTED) && (try_mark < 5)) {
    Serial.println("Try WiFi...");
    delay(1000);
    try_mark++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wifi Connected");
    delay(100);
    if (pingGoogle()) {  // ping google to check internet
      Serial.println("Connected to Internet");
      delay(100);
      wifi_mark = true;
      net_mark = true;
      free_mark = false;
      connectivity_mark = CONNECT2WIFI;
      ptr_MQTT = &wifi_MQTT;
      WiFi.setAutoReconnect(true);
      WiFi.persistent(true);
      // time seeting
      time_Client.begin();
      time_Client.forceUpdate();
      return true;
    } else {
      Serial.println("No Internet..");
      free_mark = false;
      wifi_mark = false;
      net_mark = false;
      return false;
    }
  } else {
    wifi_mark = false;
    net_mark = false;
    return false;
  }
}

bool checkWifi(){
  if (connectivity_mark == CONNECT2WIFI) {
      if (WiFi.status() != WL_CONNECTED) {
        wifi_mark = false;
        net_mark = false;
        textPrint("Wifi disconnected",50);
        return false;
      }
      else{
        return true;
      }
    }
    return false;
}

bool setWifiProfile(String the_ssid, String the_pass){
  local_wifi_ssid = the_ssid;
  local_wifi_pass = the_pass;
  pCheckWifi = checkWifi;
  pConnectWifi = connectWifi;
  return true;
}
