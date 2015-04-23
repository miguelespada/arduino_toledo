#include "ArduinoWrapper.h"


ArduinoWrapper::ArduinoWrapper(){
    bArduinoConnected = false;
    arduino = new ofArduino;
    ofAddListener(ofEvents().update, this, &ArduinoWrapper::update);
}

ArduinoWrapper::~ArduinoWrapper(){
    if(bArduinoConnected){
        arduino->disconnect();
        delete arduino;
    }
}

string ArduinoWrapper::getPort(){
    ofSerial serial;
    vector <ofSerialDeviceInfo> deviceList =  serial.getDeviceList();
    for (int i=0; i<deviceList.size(); i++) {
        if(deviceList[i].getDeviceName().find("tty.usbmodem") != std::string::npos){
            return deviceList[i].getDeviceName();
        }
    }
    return "";
};

void ArduinoWrapper::connectArduino(string deviceName){
    bArduinoConnected = arduino->connect(deviceName, 57600);
    ofAddListener(arduino->EInitialized, this, &ArduinoWrapper::setupArduino);
}

//--------------------------------------------------------------
void ArduinoWrapper::setupArduino(const int & version) {
    ofRemoveListener(arduino->EInitialized, this, &ArduinoWrapper::setupArduino);
    
    for(int i = 2; i < 10; i ++){
        arduino->sendDigitalPinMode(i, ARD_INPUT);
        arduino->sendDigital(i, ARD_HIGH);
    }
}

//--------------------------------------------------------------
void ArduinoWrapper::update(){
    if(bArduinoConnected) {
        
        arduino->update();
        
        
        if(readEncoder(0)){
            osc->sendAction("/wheel_0", encoderValue[0]);
        }
        if(readEncoder(1)){
            osc->sendAction("/wheel_1", encoderValue[1]);
        }
        
        for(int i = 0; i < 4; i ++){
            if(readValue(i))
                osc->sendAction("/palanca_" + ofToString(i), value[i]);
                
        }
        
        ofSendMessage("[Info] Arduino connected");
        ofSendMessage("[Info] Encoder 1: " + ofToString(encoderValue[0]));
        ofSendMessage("[Info] Encoder 2: " + ofToString(encoderValue[1]));
        ofSendMessage("[Info] Palanca 1: " + ofToString(value[0]));
        ofSendMessage("[Info] Palanca 2: " + ofToString(value[1]));
        ofSendMessage("[Info] Palanca 3: " + ofToString(value[2]));
        ofSendMessage("[Info] Palanca 4: " + ofToString(value[3]));
        
    }
    else{
        ofSendMessage("[Info] Arduino NOT connected"); 
    }
    if(ofGetFrameNum() % 60 == 0)
        reconnect();
    
}

bool ArduinoWrapper::readEncoder(int i){
    int pin_0;
    int pin_1;
    
    if(i == 0){
        pin_0 = 2;
        pin_1 = 3;
    }
    else{
        pin_0 = 4;
        pin_1 = 5;
    }
    
    int MSB = arduino->getDigital(pin_0); //MSB = most significant bit
    int LSB =  arduino->getDigital(pin_1); //LSB = least significant bit
    
    int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
    int sum  = (lastEncoded[i] << 2) | encoded; //adding it to the previous encoded value
    
    
    bool hasChanged = true;
    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue[i] ++;
    else if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue[i] --;
    else hasChanged = false;
    lastEncoded[i] = encoded; //store this value for next time
    return hasChanged;
}

bool ArduinoWrapper::readValue(int i){
    
    int pin = 6 + i;
    value[i] = arduino->getDigital(pin);
    
    bool hasChanged = (value[i] == lastValue[i]);
    
    lastValue[i] = value[i];
    
    return hasChanged;
}

void ArduinoWrapper::reconnect(){
    if(ofGetFrameNum() % 90 == 0){
        string deviceName = getPort();
        if(deviceName == "" && bArduinoConnected){
            arduino->disconnect();
            bArduinoConnected = false;
        }
        if(deviceName != "" && !bArduinoConnected){
            connectArduino(deviceName);
        }
    }
}


//--------------------------------------------------------------
void ArduinoWrapper::update(ofEventArgs &args){
    update();
}


