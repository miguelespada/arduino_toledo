#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
    ofBackground(54, 54, 54);
    
    soundStream.listDevices();
    soundStream.setup(this, 0, 2, 44100, 256, 4);
    left.osc = &osc;
    right.osc = &osc;
    arduino.osc = &osc;
}

//--------------------------------------------------------------
void testApp::update(){
    left.update();
    right.update();
};


//--------------------------------------------------------------
void testApp::draw(){
    info.draw();
    ofTranslate(220, 20);
    left.draw();
    ofTranslate(0, 250);
    right.draw();
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