#define WIFI_USE    //define this if using wifi before including Hendi-Internet library
// #define LAN_USE   //define this if using LAN before including Hendi-Internet library
#include "Hendi-Internet.h"

String wifi_name = "Hendi";  
String wifi_pass = "hendihart";
unsigned long the_millis=0;

void login_message(){     //not mandatory
  // Serial.println("Pura2nya publish saat pertama kali login mqtt");
  ptr_MQTT->publish("hendi/test-out/", "hehee");
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("WelCum");
  
  if(true){   // set profile
    setWifiProfile(wifi_name, wifi_pass);   //example already set with nocola dev atas wifi
    setMQTTProfile(EXAMPLE_NODE_CODE, login_message);   //example node code is "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
  }

  if(true){   // add in_topic
    addInTopic("hendi/test-in/");
  }

  while(WiFi.status() != WL_CONNECTED){   // connect wifi
    connectWifi();
    Serial.println("hee"); delay(5000);
  }
 
  connectMQTT();  // connect to mqtt

}

void loop() {

  ptr_MQTT->loop();

  connectivityEstablishment();    // include connectivity checking for every 10 seconds and auto reconnect for all type connection and mqtt
  
  if(millis() - the_millis > 10000){
    getTimeWifi();
    the_millis = millis();
  }
}
