/*
    Pump.cpp - Library for Vaxer air pump functions
    Authored by ElDiabloRojo
*/

#include <Arduino.h>
#include <Pump.h>

Pump::Pump(int enablePin, int driverPin1, int driverPin2)
{
    pinMode(driverPin1, OUTPUT);
    pinMode(driverPin2, OUTPUT);
    _enablePin = enablePin;
    _driverPin1 = driverPin1;
    _driverPin2 = driverPin2;
}

void Pump::on()
{
  analogWrite(_enablePin, 1023); 
  digitalWrite(_driverPin1, HIGH);
  digitalWrite(_driverPin2, LOW);
}

void Pump::off()
{
  analogWrite(_enablePin, 0); 
  digitalWrite(_driverPin1, LOW);
  digitalWrite(_driverPin2, LOW);
}