#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* mqttServer = "MQTT_SERVER_IP";
const int mqttPort = 1883;

const char* message;

const int IN1 = 13;
const int IN2 = 15;
const int ENA = 12;
const int IN3 = 4;
const int IN4 = 0;
const int ENB = 2;

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
      airOn();
    break;
    case 'O':
      airOff();
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

void airOn(){
  analogWrite(ENB, 1023); 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void airOff(){
  analogWrite(ENB, 0); 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void feed() {
  while(analogRead(liquidLevelPin) < highLevel) {
    Serial.println("feeding");
    Serial.println("water level left to fill: ");
    Serial.print(highLevel - analogRead(liquidLevelPin));
    analogWrite(ENA, 1023); 
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  Serial.println("high watermark reached, emptying");
  while(analogRead(liquidLevelPin) > lowLevel) {
    Serial.println("draining");
    Serial.println("water level remaing: ");
    Serial.print(analogRead(liquidLevelPin) - lowLevel);
    analogWrite(ENA, 1023); 
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  Serial.println("feed complete");
  Serial.println("water level: ");
  Serial.print(analogRead(liquidLevelPin));
  analogWrite(ENA, 0); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
  
void setup() {
  Serial.begin(9600);
  pinMode(liquidLevelPin, INPUT);
  pinMode(planterLight, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENB, OUTPUT);

 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
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
 
  client.subscribe("topic/vaxcer");
}
 
void loop() {
  client.loop();
}
