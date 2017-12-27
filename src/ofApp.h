#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFiducialFinder.h"
#include "ofxFiducialTracker.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

#include "Vegetable.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    int mappedFiducialXpos;
    int mappedFiducialYpos;
    
    int threshold;
    bool bLearnBakground;
    bool backgroundSubOn;
    
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvColorImage colorImg;
    
    ofImage carrotImg;
    
    ofImage carrot;
    ofImage parsnip;
    ofImage radish;
    ofImage salad;
    ofImage tomato;
    ofImage ground;
    
    ofSoundPlayer plantSeedSound;
    ofSoundPlayer bgSound;
    
    ofVideoPlayer testVideo;
    
    vector<Vegetable *> vegetables;
    
    ofxKinect kinect;
    ofxFiducialTracker fidfinder;
};
