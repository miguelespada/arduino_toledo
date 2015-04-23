//
//  Settings.h
//  carrousel
//
//  Created by miguel on 12/10/14.
//
//

#ifndef __Settings__
#define __Settings__

#include "ofxJSON.h"
#include "ofMain.h"

class Settings{
public:
    static Settings* getInstance();
    void load();
    
    int getRemotePort();
    string getRemoteHost();
    
private:
    static Settings* instance;
    Settings();
    Settings(Settings const&);
    void operator=(Settings const&);
    
    ofxJSONElement json_file;
    Json::Value getData(string key);
};
#endif
