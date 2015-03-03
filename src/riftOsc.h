//
//  riftOsc.h
//  OculusPanoramaDK1
//
//  Created by Martijn Mellema on 03-03-15.
//
//

#ifndef __OculusPanoramaDK1__riftOsc__
#define __OculusPanoramaDK1__riftOsc__

#include <stdio.h>
#include "ofMain.h"

#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

class mainRift;

class riftOsc
{
private:

    ofxOscSender sender;
    ofxOscReceiver receiver;
    mainRift* riftDelegate;
public:
    ~riftOsc();
    void setup(mainRift * delegate);
    void update(ofEventArgs &data);
    void sendRift(ofMatrix4x4  mat, float time, float endTime, bool isDone);
    
};


#endif /* defined(__OculusPanoramaDK1__riftOsc__) */
