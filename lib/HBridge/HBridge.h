/*
    HBridge.h - Library for Vaxer h bridge functions
    Authored by ElDiabloRojo
*/

#ifndef HBridge_h
#define HBridge_h

#include <Arduino.h>

class HBridge {
    public:
        HBridge(int enablePin, int driverPin1, int driverPin2);
        void forward(int enableSetting);
        void reverse(int enableSetting);
        void disable();
    private:
        int _enablePin;
        int _driverPin1;
        int _driverPin2;
};

# endif
