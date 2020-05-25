#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <HBridge.h>
#include <Relay.h>


const char* wifiSsid = WIFI_SSID;
const char* wifiPasswd = WIFI_PASSWD;
const char* mqttBrokerAddr = MQTT_BROKER_IPADDR;
const int mqttBrokerPort = MQTT_BROKER_PORT;

const char* message;

const int liquidLevelPin = 15;

HBridge pumpOne(4, 0, 2);
HBridge pumpTwo(14, 13, 12);

Relay planterLight(5);

WiFiClient espClient;
PubSubClient client(espClient);

int drainDuration;
int drainTime;
int feedFillTime;
int feedStartTime;

 
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
    case 'Z': 
      feedStartTime = millis();
      pumpOne.forward(1023);
    break;
    case 'A':
      pumpOne.forward(1023);
    break;
    case 'C':
      pumpOne.disable();
    break;
    case 'D':
      pumpTwo.forward(1023);
    break;
    case 'F':
      pumpTwo.disable();
    break;
    case 'G':
      planterLight.toggle();
    break;
    case 'H':
      planterLight.on();
    break;
    case 'I':
      planterLight.off();
    break;
    default: 
      Serial.println("no message received"); 
    break;
  }
}
  
void setup() {
  Serial.begin(9600);
  pinMode(liquidLevelPin, INPUT);
 
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
 
    if (client.connect("ESP8266 Client")) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }
 
  client.subscribe("vaxer/actions");
}
 
void loop() {
  unsigned long currentMillis = millis();

  client.loop();

  if (digitalRead(liquidLevelPin) == HIGH) {
    feedFillTime = currentMillis;
    pumpOne.disable();
    pumpTwo.forward(1023);
    drainDuration = feedFillTime - feedStartTime;
    drainTime = currentMillis + drainDuration;
  }

  if (currentMillis >= drainTime) {
    pumpTwo.disable();
  }


}
