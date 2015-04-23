#include "testApp.h"
#include "Settings.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
    ofBackground(54, 54, 54);
    
    bAudio = Settings::getInstance()->useAudio();
    
    if(bAudio){
        soundStream.listDevices();
        soundStream.setup(this, 0, 2, 44100, 256, 4);
        left.osc = &osc;
        right.osc = &osc;
    }
    else
    {
     arduino.osc = &osc;
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
    if(bAudio){
        left.update();
        right.update();
    }
};


//--------------------------------------------------------------
void testApp::draw(){
    info.draw();
    if(bAudio){
        ofTranslate(220, 20);
        left.draw();
        ofTranslate(0, 250);
        right.draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
    left.add(input, 0);
    right.add(input, 1);
}