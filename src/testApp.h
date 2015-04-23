#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ArduinoWrapper.h"
#include "Info.h"
#include "buffer.h"
#include "OscAdapter.h"


class testApp : public ofSimpleApp{
    
public:
    
	void setup();
	void update();
	void draw();
    
	void keyPressed(int key);
	void keyReleased(int key);
    
    ArduinoWrapper	arduino;
    Info info;
        
    void audioIn(float * input, int bufferSize, int nChannels);
    
    Buffer left;
    Buffer right;
    
    ofSoundStream soundStream;
    OscAdapter osc;
    bool bAudio;
};

