//
//  buffer.cpp
//  pull_arduino_paris
//
//  Created by miguel on 21/04/15.
//
//

#include "buffer.h"

Buffer::Buffer(){
    
    data.assign(256, 0.0);
    volHistory.assign(256, 0.0);
    smoothedVol     = 0.0;
    scaledVol		= 0.0;

}

void Buffer::update(){
    //lets scale the vol up to a 0-1 range
  //  scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, false);
    //lets record the volume into an array
    volHistory.push_back( acc/10 );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 256 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
}

void Buffer::draw(){
    // draw the right channel:
    ofPushStyle();
    ofPushMatrix();
    
    ofNoFill();
    ofSetLineWidth(0.5);
    ofRect(0, 0, 512, 200);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    
    ofBeginShape();
    for (unsigned int i = 0; i < data.size(); i++){
        ofVertex(i*2, 100 -data[i]*180.0f);
    }
    ofEndShape(false);
    
    ofTranslate(0, 200);
    ofSetColor(245, 58, 235);
    ofSetLineWidth(1);
    
    //lets draw the volume history as a graph
    ofBeginShape();
    for (unsigned int i = 0; i < volHistory.size(); i++){
        if( i == 0 ) ofVertex(i, 256);
        
        ofVertex(i,  - volHistory[i] * 70);
        
        if( i == volHistory.size() -1 ) ofVertex(i, 0);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
    
}

void Buffer::add(float *values, int pair){
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < 256; i++){
        data[i]		= values[i * 2 + pair];
        curVol += data[i] * data[i];
        numCounted+=1;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;

    acc += smoothedVol;
    acc *= 0.99;
    
    
    if(int(prevAcc * 10) != int(acc * 10) ){
        if(pair == 0)
            osc->sendAction("/left", int(acc*10));
        if(pair == 1)
            osc->sendAction("/right", int(acc*10));
    }
    
    prevAcc = acc;
    
    
    
}