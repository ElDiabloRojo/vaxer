/*
    Relay.cpp - Library for Vaxer relay functions
    Authored by ElDiabloRojo
*/

#include <Arduino.h>
#include <Relay.h>

Relay::Relay(int relayPin)
{
    pinMode(relayPin, OUTPUT);
    int _relayState = HIGH;
    _relayPin = relayPin;
}

void Relay::toggle()
{
  if (_relayState == HIGH) {
    _relayState = LOW;
  } else {
    _relayState = HIGH;
  }
  digitalWrite(_relayPin, _relayState);
}

void Relay::off()
{
  digitalWrite(_relayPin, HIGH);
}

void Relay::on()
{
  digitalWrite(_relayPin, LOW);
}