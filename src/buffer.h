//
//  buffer.h
//  pull_arduino_paris
//
//  Created by miguel on 21/04/15.
//
//

#ifndef __pull_arduino_paris__buffer__
#define __pull_arduino_paris__buffer__

#include "ofMain.h"
#include "OscAdapter.h"

class Buffer
{
    vector <float> data;
    vector <float> volHistory;

    float smoothedVol;
    float scaledVol;
    float acc;
    float prevAcc;
    
public:
    Buffer();
    void draw();
    void update();
    void add(float *values, int pair);
    OscAdapter *osc;
    int threshold;
    
};

#endif /* defined(__pull_arduino_paris__buffer__) */
