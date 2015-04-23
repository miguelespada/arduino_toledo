#include "Settings.h"

Settings::Settings(){
}

Settings* Settings::instance = 0;
Settings* Settings::getInstance(){
    if (instance == 0){
        instance = new Settings();
        instance->load();
    }
    return instance;
};

void Settings::load(){
    ofSetDataPathRoot("./data/");
    string path = ofToDataPath("settings.json", true);
    ofLogNotice() << "Loading settings from: " << path;
    json_file.open(path);
}

Json::Value Settings::getData(string key){
    return Settings::json_file[key];
}


int Settings::getRemotePort(){
    return getData("remote_port").asInt();
}

string Settings::getRemoteHost(){
    return getData("remote_host").asString();
}

