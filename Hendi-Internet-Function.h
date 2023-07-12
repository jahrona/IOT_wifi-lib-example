#ifndef Hendi-Internet-Function_h
#define Hendi-Internet-Function_h
#endif

#include <ESP32Ping.h>

bool blankBoolFunction(){return true;}
bool blankBoolFunction2(String xyz, String abc){return true;}


typedef bool (*pointerF)();
typedef bool (*pointerF2)(String abcd, String efgh);
// typedef void (*pointerF3)();

pointerF pCheckWifi = blankBoolFunction;
pointerF pCheckLan = blankBoolFunction;
pointerF2 pConnectWifi = blankBoolFunction2;

// pointerF3 pTestF;
// pointerF pCheckWifi, pConnectLan, pCheckLan;
// pointerF2 pConnectWifi;

void textPrint(String the_words, unsigned long the_delay){
  Serial.println(the_words); delay(the_delay);
}

bool pingGoogle() {
  net_mark = Ping.ping("www.google.com", 3);
  return net_mark;
}

void connectivityCheck() {
  if (millis() - net_millis >= check_net_interval) {
    pCheckLan();
    pCheckWifi();
    net_millis = millis();
  }

  if (millis() - mqtt_millis >= check_mqtt_interval) {
    if (!ptr_MQTT->connected()) {
      mqtt_mark = false;
    }
  }
}

void reconnectAttempt(){
  if (connectivity_mark == CONNECT2LAN){
  }
  else if(connectivity_mark == CONNECT2WIFI){
    if(wifi_mark == false){
      pConnectWifi(local_wifi_ssid, local_wifi_pass);
    }
  }
  if (net_mark == true){
    if (mqtt_mark == false){
      connectMQTT();
    }
  }
}

void connectivityEstablishment(){
  connectivityCheck();
  reconnectAttempt();
}