# Vaxer
This repository contains source files for Vaxer; an adapted indoor growing unit,
driven by a NodeMCU microcontroller.

The microcontroller is programmed to connect to a wifi network, subscribe to a
message queue & perform actions to support the growth of the plants it contains.

## This Project
The code in this repository is written using 
[vscode](https://code.visualstudio.com/) with the 
[platformio](https://platformio.org/install/ide?install=vscode) extension.

## Environment
Microcontroller configuration is supplied via environment variables and should 
be exported prior to compiling the code, they are as follows:

* WIFI_SSID
* WIFI_PASSWD
* MQTT_BROKER_IPADDR
* MQTT_BROKER_PORT

PlatformIO has some issues with parsing, escaping some characters is necessary,
please see these examples:

```
export WIFI_SSID='\"Router123\"'
export WIFI_PASSWD='\"69Security\!\"'
export MQTT_BROKER_IPADDR='\"192\.168\.0\.4\"'
export MQTT_BROKER_PORT=1883
```

## Messages
Vaxer is programmed to process 4 individual messages:

* "F", Feed, this function will pump water from the reservoir into the planters 
feeding tray until the water sensor records a predefined "high" water level, at 
this point the current to the water pump motor is reversed draining the tray 
until the "low" water level is reached, ending the function.

* "A", Enable Aeration, this message enables the air pump, aerating the water in 
the reservoir, this will run until Vaxer recieves the message to disable the 
pump.

* "O", Disable Aeration, the air pump will be disabled when this message is 
received.

* "L", Lights, recieving this message will toggle the light on & off.


## Circuit Diagram

![annotated circuit diagram made with fritzing](./docs/annotated-circuit.png)

## Collaboration

(slack)[slack://channel?id=vaxer]
