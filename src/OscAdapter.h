//
//  OscAdapter.h
//  pull_arduino
//
//  Created by miguel on 30/10/14.
//
//

#ifndef __pull_arduino__OscAdapter__
#define __pull_arduino__OscAdapter__

#include <stdio.h>

#include "ofxOsc.h"

class OscAdapter{
    
    ofxOscSender sender;
public:
    OscAdapter();
    
    void update(ofEventArgs &args);
    
    string host;
    int port;
    void sendAction(string msg);
    void sendAction(string msg, int v);
};
#endif /* defined(__pull_arduino__OscAdapter__) */
