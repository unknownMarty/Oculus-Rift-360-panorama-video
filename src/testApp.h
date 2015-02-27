#pragma once

#include "ofMain.h"

//#define DK2
//#define DK2
#if defined(DK2)
#include "ofxOculusDK2.h"
#endif

#if defined(DK1)
#include "ofxOculusRift.h"
#endif

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
    enum Eye
    {
        LEFT_EYE,
        RIGHT_EYE
    };
	
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
    
    void beginEye(Eye eye);
    void endEye(Eye eye);
#if defined(DK2)
	ofxOculusDK2		oculusRift;
#endif
    
#if defined(DK1)
    ofxOculusRift		oculusRift;
#endif
	ofLight				light;
	ofEasyCam			cam;
	bool showOverlay;
	bool predictive;

    
    ofVec3f cursor2D;
    ofVec3f cursor3D;
    
    ofVec3f cursorRift;
    ofVec3f demoRift;
    
    ofVec3f cursorGaze;
    
    ofQTKitPlayer movie;
    

    map<Eye,ofFbo*> videoEyes;
   // ofFbo leftEye;
   // ofFbo rightEye;
    
    void drawVideoOnSphere(Eye eye);
};
