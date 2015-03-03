//
//  mainRift.h
//  OculusPanoramaDK1
//
//  Created by Martijn Mellema on 03-03-15.
//
//

#ifndef __OculusPanoramaDK1__mainRift__
#define __OculusPanoramaDK1__mainRift__

#include <stdio.h>
#include "ofMain.h"
#include "riftOsc.h"

#if defined(DK2)
#include "ofxOculusDK2.h"
#endif

#if defined(DK1)
#include "ofxOculusRift.h"
#endif

typedef enum
{
    LEFT_EYE,
    RIGHT_EYE
}Eye;


class mainRift
{
private:
#if defined(DK2)
    ofxOculusDK2		oculusRift;
#endif
#if defined(DK1)
    ofxOculusRift		oculusRift;
#endif

    map<Eye,ofFbo*> videoEyes;
    
    riftOsc osc;
    vector<ofQTKitPlayer*> movies;
    

public:
    mainRift();
    ~mainRift();
    void setup();
    void draw(ofEventArgs &data);
    void update(ofEventArgs &data);
    void beginEye(Eye eye);
    void endEye(Eye eye);
    void drawVideoOnSphere(Eye eye);
    
    void addMovie(string filename);
    void stop(int id);
    void play(int id);

};

#endif /* defined(__OculusPanoramaDK1__mainRift__) */
