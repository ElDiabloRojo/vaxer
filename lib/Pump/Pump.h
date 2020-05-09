/*
    Pump.h - Library for Vaxer air pump functions
    Authored by ElDiabloRojo
*/

#ifndef Pump_h
#define Pump_h

#include <Arduino.h>

class Pump {
    public:
        Pump(int enablePin, int driverPin1, int driverPin2);
        void on();
        void off();
    private:
        int _enablePin;
        int _driverPin1;
        int _driverPin2;
};

# endif
