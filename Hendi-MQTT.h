#ifndef Hendi-MQTT_h
#define Hendi-MQTT_h
#endif

#ifndef IN_TOPIC_TOTAL
#define IN_TOPIC_TOTAL 9
#endif

PubSubClient* ptr_MQTT;

const char* mqttServer = "mqtt.nocola.co.id";
const int mqttPort = 1883;
const char* mqttUser = "mqtt_nocola";
const char* mqttPassword = "cinta123";

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80); 
  const char *APSSID = "FLUX DEVICE";
  const char *APPSK = "flux2022";

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 2, 232);
IPAddress dns(8,8,8,8);
unsigned int localPort = 37;       // local port to listen for UDP packets
const char timeServer[] = "id.pool.ntp.org"; // time.nist.gov NTP server
IPAddress timeServerIP = IPAddress(103,177,8,230);
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

#ifdef IN_TOPIC_TOTAL > 0
  const char* topic_pointer[IN_TOPIC_TOTAL];
  unsigned int current_in_topic_total = 0;
  void addInTopic(const char* the_topic){
    if(current_in_topic_total < IN_TOPIC_TOTAL){
    topic_pointer[current_in_topic_total] = the_topic;
    current_in_topic_total++;
    }
    else{
      Serial.println("Max topics amount already reached");
    }
  }
#endif

typedef void (*pointerPingFunction)();
pointerPingFunction pingFunction;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(":v");
}

void nothingFunction(){}

bool setMQTTProfile(String the_node_code, void (*_PingFunction)() = nothingFunction){
  local_node_code = the_node_code;
  pingFunction = _PingFunction;
  return true;
}

// bool connectMQTT(PubSubClient* the_pointer, String the_node_code = local_node_code, void (*pingFunction)() = nothingFunction) {
bool connectMQTT(String the_node_code = local_node_code,  PubSubClient* the_pointer = ptr_MQTT){
  ptr_MQTT->setServer(mqttServer, mqttPort);
  ptr_MQTT->setCallback(callback);
  if (ptr_MQTT->connect(the_node_code.c_str(), mqttUser, mqttPassword)) {
    Serial.println("MQTT Connected"); delay(100);
    if (true) {  //subscribe
      for(int i =0; i<current_in_topic_total; i++){
        ptr_MQTT->subscribe(topic_pointer[i]);
      }
    }
    // (*pingFunction)();
    pingFunction();
    mqtt_mark = true;
    ping_mark = true;
    return true;
  } else {
    Serial.println("Failed to connect to MQTT");
    delay(50);
    mqtt_mark = false;
    return false;
  }
}