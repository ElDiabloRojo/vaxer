/*
    Relay.h - Library for Vaxer relay functions
    Authored by ElDiabloRojo
*/

#ifndef Relay_h
#define Relay_h

#include <Arduino.h>

class Relay {
    public:
        Relay(int relayPin);
        void toggle();
        void on();
        void off();
    private:
        int _relayPin;
        int _relayState;
};

# endif
