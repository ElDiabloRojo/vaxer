/*
    HBridge.cpp - Library for Vaxer h bridge functions
    Authored by ElDiabloRojo
*/

#include <Arduino.h>
#include <HBridge.h>

HBridge::HBridge(int enablePin, int driverPin1, int driverPin2)
{
    pinMode(driverPin1, OUTPUT);
    pinMode(driverPin2, OUTPUT);
    _enablePin = enablePin;
    _driverPin1 = driverPin1;
    _driverPin2 = driverPin2;
}

void HBridge::forward(int enableSetting)
{
  analogWrite(_enablePin, enableSetting); 
  digitalWrite(_driverPin1, HIGH);
  digitalWrite(_driverPin2, LOW);
}

void HBridge::reverse(int enableSetting)
{
  analogWrite(_enablePin, enableSetting); 
  digitalWrite(_driverPin1, LOW);
  digitalWrite(_driverPin2, HIGH);
}

void HBridge::disable()
{
  analogWrite(_enablePin, 0); 
  digitalWrite(_driverPin1, LOW);
  digitalWrite(_driverPin2, LOW);
}