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
    receiver.setup(12346);
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
    //    stringstream str;
    //
    //
    //    str<<mat;
    //    string matrix = str.str();
    //    vector<string> l = ofSplitString(matrix, "\n");
    //    m.addIntArg(l.size());
    //    for(auto line : l)
    //    {
    //        ofStringReplace(line, " ", "");
    //        m.addStringArg( line);
    //    }
    
    //    str.clear();
    
    ofxOscMessage m;
   
    m.setAddress("HeadsetOrientationMat");
    

    ofQuaternion q = mat.getRotate();
    cout<<q<<endl;
    m.addFloatArg(q.x());
    m.addFloatArg(q.y());
    m.addFloatArg(q.z());
    m.addFloatArg(q.w());
    
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

