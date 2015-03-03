//
//  mainRift.cpp
//  OculusPanoramaDK1
//
//  Created by Martijn Mellema on 03-03-15.
//
//

#include "mainRift.h"

mainRift::mainRift()
{
    
 
}
mainRift::~mainRift()
{
    ofRemoveListener(ofEvents().draw, this, &mainRift::draw);
    ofRemoveListener(ofEvents().update, this, &mainRift::update);
    delete videoEyes[LEFT_EYE];
    delete videoEyes[RIGHT_EYE];
    
    for(int x=0; x< movies.size(); x++)
    {
        delete movies[x];
    }
}


void mainRift::setup()
{
    
#if defined(DK2)
    oculusRift.baseCamera = &cam;
    oculusRift.setup();
#endif
    
#if defined(DK1)
    oculusRift.init( ofGetWidth(), ofGetHeight(), 4 );
    oculusRift.setPosition( 0,-30,0 );
#endif
    
    
    videoEyes[LEFT_EYE] = new ofFbo();
    videoEyes[RIGHT_EYE] = new ofFbo();
    
    ofAddListener(ofEvents().draw, this, &mainRift::draw);
    ofAddListener(ofEvents().update, this, &mainRift::update);
    
    osc.setup(this);
    
}



void mainRift::addMovie(string filename)
{
    //    ofBackground(255, 255, 255);

    // #1 Play videos with an alpha channel. ---------------------------
    // ofQTKitPlayer videos encoded with Alpha channels (e.g. Animation Codec etc).
    // The pixel format MUST be enabled prior to loading!
    // If an alpha channels is not used, setting a non-alpha pixel format
    // (e.g. OF_PIXELS_RGB) will increase performance.
    movies.push_back(new ofQTKitPlayer());
    movies.back()->setPixelFormat(OF_PIXELS_RGB);
    
    // Pixels and texture together is faster than PIXEL_ONLY and manually uploaded textures.
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    
    movies.back()->loadMovie(filename, decodeMode);
//    movies.back()->setPosition(.5);
    //movies.back()->play();
    
    videoEyes[LEFT_EYE]->allocate(movies.back()->getWidth(), movies.back()->getHeight()/2);
    videoEyes[RIGHT_EYE]->allocate(movies.back()->getWidth(), movies.back()->getHeight()/2);


}

void mainRift::stop(int id)
{
    movies.at(id)->stop();
}

void mainRift::play(int id)
{
    for(int x=0; x< movies.size(); x++)
    {
        if(id == x)
            movies.at(x)->play();
        else
            movies.at(x)->stop();
    }
}

void mainRift::update(ofEventArgs &data)
{
    for(int x=0; x< movies.size(); x++)
    {
        movies.at(x)->update();
        if(movies.at(x)->isPlaying())
        {
            videoEyes[LEFT_EYE]->begin();
            if(!movies.at(x)->getIsMovieDone())
                movies.at(x)->draw(0, 0);
            videoEyes[LEFT_EYE]->end();
            
            videoEyes[RIGHT_EYE]->begin();
            movies.at(x)->draw(0,  -movies.at(x)->getHeight()/2);
            videoEyes[RIGHT_EYE]->end();
            
            osc.sendRift(oculusRift.getHeadsetOrientationMat() ,
                         movies.at(x)->getPositionInSeconds(),
                         movies.at(x)->getDuration(),
                         movies.at(x)->getIsMovieDone());
        }
        
    }
    
    
}


void mainRift::draw(ofEventArgs &data)
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

void mainRift::beginEye(Eye eye)
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

void mainRift::endEye(Eye eye)
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


void mainRift::drawVideoOnSphere(Eye eye)
{
    ofPushMatrix();
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
