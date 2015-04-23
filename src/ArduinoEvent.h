//
//  Events.h
//  planta
//
//  Created by miguel on 21/02/15.
//
//

#ifndef planta_Events_h
#define planta_Events_h
#pragma once
#include "ofMain.h"

class ArduinoEvent : public ofEventArgs {
    
public:
    
    int pin;
    int value;
    
    ArduinoEvent() {}
    ArduinoEvent(int _pin, int _value) {
        pin = _pin;
        value = _value;
    }
    
    static ofEvent <ArduinoEvent> digitalEvents;
};

#endif
