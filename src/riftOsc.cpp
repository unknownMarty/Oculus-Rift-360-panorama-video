//
//  riftOsc.cpp
//  OculusPanoramaDK1
//
//  Created by Martijn Mellema on 03-03-15.
//
//

#include "riftOsc.h"
#include "mainRift.h"

riftOsc::~riftOsc()
{
    ofRemoveListener(ofEvents().update, this, &riftOsc::update);
}

void riftOsc::setup(mainRift * delegate)
{
    
    // open an outgoing connection to HOST:PORT
    sender.setup(HOST, PORT);
    riftDelegate = delegate;
    ofAddListener(ofEvents().update, this, &riftOsc::update);
}

void riftOsc::update(ofEventArgs &data)
{
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        if(m.getAddress() == "play")
        {
            int movieID = m.getArgAsInt32(0);
            riftDelegate->play(movieID);
        }
        if(m.getAddress() == "stop")
        {
            int movieID = m.getArgAsInt32(0);
            riftDelegate->stop(movieID);
        }
    }
}

void riftOsc::sendRift(ofMatrix4x4  mat,
                       float time,
                       float endTime,
                       bool isDone)
{
    
    ofxOscMessage m;
   
    m.setAddress("HeadsetOrientationMat");
    stringstream str;
    str<<mat;
    m.addStringArg(str.str());
    str.clear();
    
    sender.sendMessage(m);
    m.clear();
    
    m.setAddress("time");
    m.addFloatArg(time);
    
    sender.sendMessage(m);
    m.clear();
    
    m.setAddress("endTime");
    m.addFloatArg(endTime);
    
    sender.sendMessage(m);
    m.clear();
    
    m.setAddress("isVideoDone");
    m.addIntArg(isDone);
    
    sender.sendMessage(m);
    m.clear();
   
}

