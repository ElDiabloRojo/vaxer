#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <HBridge.h>


const char* wifiSsid = WIFI_SSID;
const char* wifiPasswd = WIFI_PASSWD;
const char* mqttBrokerAddr = MQTT_BROKER_IPADDR;
const int mqttBrokerPort = MQTT_BROKER_PORT;

const char* message;

HBridge aeration(4, 0, 2);
HBridge water(12, 13, 15);

const int IN1 = 13;
const int IN2 = 15;
const int ENA = 12;

const int planterLight = 5;
int planterState = HIGH;

const int liquidLevelPin = A0;
int liquid_level;
const int highLevel = 420;
const int lowLevel = 220;

WiFiClient espClient;
PubSubClient client(espClient);
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    readmessage((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}

void readmessage(char message){
  switch(message){
    case 'F': 
      feed();
    break;
    case 'A':
      aeration.forward(1023);
    break;
    case 'O':
      aeration.disable();
    break;
    case 'L':
      lights();
    break;
    default: 
      Serial.println("no message received"); 
    break;
  }
}

void lights() {
  if (planterState == HIGH) {
    planterState = LOW;
  } else {
    planterState = HIGH;
  }
  digitalWrite(planterLight, planterState);
}

void feed() {
  while(analogRead(liquidLevelPin) < highLevel) {
    Serial.println("feeding");
    Serial.println("water level left to fill: ");
    Serial.print(highLevel - analogRead(liquidLevelPin));
    water.forward(1023);
  }
  Serial.println("high watermark reached, emptying");
  while(analogRead(liquidLevelPin) > lowLevel) {
    Serial.println("draining");
    Serial.println("water level remaing: ");
    Serial.print(analogRead(liquidLevelPin) - lowLevel);
    water.reverse(1023);
  }
  Serial.println("feed complete");
  Serial.println("water level: ");
  Serial.print(analogRead(liquidLevelPin));
  water.disable();
}
  
void setup() {
  Serial.begin(9600);
  pinMode(liquidLevelPin, INPUT);
  pinMode(planterLight, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);

 
  WiFi.begin(wifiSsid, wifiPasswd);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttBrokerAddr, mqttBrokerPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client")) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.subscribe("topic/vaxer");
}
 
void loop() {
  client.loop();
}
