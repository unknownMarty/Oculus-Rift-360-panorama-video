#include "testApp.h"

testApp::~testApp()
{

    delete videoEyes[LEFT_EYE];
    delete videoEyes[RIGHT_EYE];
}

//--------------------------------------------------------------
void testApp::setup()
{
	ofBackground(0);
	ofSetLogLevel( OF_LOG_VERBOSE );
	ofSetVerticalSync( true );
    
//    ofBackground(255, 255, 255);
    

    
    // #1 Play videos with an alpha channel. ---------------------------
    // ofQTKitPlayer videos encoded with Alpha channels (e.g. Animation Codec etc).
    // The pixel format MUST be enabled prior to loading!
    // If an alpha channels is not used, setting a non-alpha pixel format
    // (e.g. OF_PIXELS_RGB) will increase performance.
    movie.setPixelFormat(OF_PIXELS_RGBA);
    
    // Pixels and texture together is faster than PIXEL_ONLY and manually uploaded textures.
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    
    movie.loadMovie("music-rift-2.mov", decodeMode);
    movie.setPosition(.5);;
    movie.play();

	showOverlay = false;
	predictive = true;
	
	ofHideCursor();
#if defined(DK2)
	oculusRift.baseCamera = &cam;
	oculusRift.setup();
#endif
    
#if defined(DK1)    
    
    oculusRift.init( ofGetWidth(), ofGetHeight(), 4 );
    oculusRift.setPosition( 0,-30,0 );
#endif
		
	//enable mouse;
	cam.begin();
	cam.end();
    
    videoEyes[LEFT_EYE] = new ofFbo();
    videoEyes[RIGHT_EYE] = new ofFbo();
    videoEyes[LEFT_EYE]->allocate(movie.getWidth(), movie.getHeight()/2);
    videoEyes[RIGHT_EYE]->allocate(movie.getWidth(), movie.getHeight()/2);
    
}


//--------------------------------------------------------------
void testApp::update()
{
    movie.update();


    videoEyes[LEFT_EYE]->begin();
    movie.draw(0, 0);
    videoEyes[LEFT_EYE]->end();
    
    videoEyes[RIGHT_EYE]->begin();
    movie.draw(0,  -movie.getHeight()/2);
    videoEyes[RIGHT_EYE]->end();
}


//--------------------------------------------------------------
void testApp::draw()
{

#if defined(DK2)
	if(oculusRift.isSetup()){

		
        
        ofSetColor(255);
		
#endif
#if defined(DK1)
        oculusRift.setNeedSensorReadingThisFrame( true );
#endif
        glEnable(GL_DEPTH_TEST);
        beginEye(LEFT_EYE);
        drawVideoOnSphere(LEFT_EYE);
        endEye(LEFT_EYE);
		
        beginEye(RIGHT_EYE);
        drawVideoOnSphere(RIGHT_EYE);
		endEye(RIGHT_EYE);
        
        
#if defined(DK2)
		oculusRift.draw();
#endif
#if defined(DK1)
        ofSetColor( 255 );
        oculusRift.draw( ofVec2f(0,0), ofVec2f( ofGetWidth(), ofGetHeight() ) );
#endif
        glDisable(GL_DEPTH_TEST);
#if defined(DK2)
		

    }
#endif
	
}


void testApp::beginEye(Eye eye)
{
    switch (eye)
    {
        case LEFT_EYE:
#if defined(DK2)
            oculusRift.beginLeftEye();
            
#endif
#if defined(DK1)
            oculusRift.beginRenderSceneLeftEye();
#endif
            break;
        case RIGHT_EYE:
            
#if defined(DK2)
            oculusRift.beginRightEye();
            
#endif
#if defined(DK1)
            oculusRift.beginRenderSceneRightEye();
#endif
            
            break;
    }

    
}

void testApp::endEye(Eye eye)
{
    switch (eye)
    {
        case LEFT_EYE:
#if defined(DK2)
            oculusRift.endLeftEye();
#endif
#if defined(DK1)
            oculusRift.endRenderSceneLeftEye();
#endif
            break;
        case RIGHT_EYE:
            
#if defined(DK2)
            oculusRift.endRightEye();
#endif
#if defined(DK1)
            oculusRift.endRenderSceneRightEye();
#endif
            
            break;
    }

    
}

void testApp::drawVideoOnSphere(Eye eye)
{
    ofPushMatrix();
   //
  //  ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    ofScale(-1, 1,1);
    ofSetColor(255);
    
    
    videoEyes[eye]->getTextureReference().bind();
    
    ofMultMatrix( oculusRift.getHeadsetOrientationMat() );
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    
    ofScale(videoEyes[eye]->getWidth(), videoEyes[eye]->getHeight());
    glMatrixMode(GL_MODELVIEW);

    //draw here as before
    
    ofSphere( 1000);


    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);


    videoEyes[eye]->getTextureReference().unbind();
    ofPopMatrix();
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
#if defined(DK2)
	if( key == 'f' )
	{
		//gotta toggle full screen for it to be right
		ofToggleFullscreen();
	}
	
	if(key == 's'){
		oculusRift.reloadShader();
	}
	
	if(key == 'l'){
		oculusRift.lockView = !oculusRift.lockView;
	}
	
	if(key == 'o'){
		showOverlay = !showOverlay;
	}
	if(key == 'r'){
		oculusRift.reset();
		
	}
	if(key == 'h'){
		ofHideCursor();
	}
	if(key == 'H'){
		ofShowCursor();
	}
	
	if(key == 'p'){
		predictive = !predictive;
		oculusRift.setUsePredictedOrientation(predictive);
	}
#endif
#if defined(DK1)
    if( key == 'w' )
    {
        oculusRift.setDoWarping( !oculusRift.getDoWarping() );
    }
#endif
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
 //   cursor2D.set(x, y, cursor2D.z);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
//    cursor2D.set(x, y, cursor2D.z);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
