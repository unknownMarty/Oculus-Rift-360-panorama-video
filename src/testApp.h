#pragma once

#include "ofMain.h"
#include "mainRift.h"



/*
 DK 1 notes:
 
remove the following lines from 'ofxOculusRift::beginRender( float _interOcularShift, ofFbo* _fbo  )' :
 
 ofScale(1,1,1);
 ofMultMatrix( getHeadsetViewOrientationMat() );
 
 */



class testApp : public ofBaseApp
{
  public:
    ~testApp();
  
	
	void setup();
	void update();
	void draw();
	
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    

	ofLight				light;
	ofEasyCam			cam;
	bool showOverlay;
	bool predictive;

    
    ofVec3f cursor2D;
    ofVec3f cursor3D;
    
    ofVec3f cursorRift;
    ofVec3f demoRift;
    
    ofVec3f cursorGaze;
    
    mainRift* rift;
    
};
