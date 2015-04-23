//
//  OscAdapter.cpp
//  pull_arduino
//
//  Created by miguel on 30/10/14.
//
//

#include "OscAdapter.h"
#include "Settings.h"

OscAdapter::OscAdapter(){
    ofAddListener(ofEvents().update, this, &OscAdapter::update);

    
    host = Settings::getInstance()->getRemoteHost();
    port = Settings::getInstance()->getRemotePort();
    sender.setup(host, port);
}

void OscAdapter::sendAction(string msg){
    ofxOscMessage m;
    m.setAddress(msg);
    sender.sendMessage(m);
}


void OscAdapter::sendAction(string msg, int v){
    ofxOscMessage m;
    m.setAddress(msg);
    m.addIntArg(v);
    
    sender.sendMessage(m);
}



void OscAdapter::update(ofEventArgs &args){
    ofSendMessage("[Info] OSC " + ofToString(host) + " " + ofToString(port));
    
   
}