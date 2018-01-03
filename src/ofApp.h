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
    
    int mappedFiducialXpos;
    int mappedFiducialYpos;
    
    float vegetableZeroPlantedTime;
    float vegetableOnePlantedTime;
    float vegetableTwoPlantedTime;
    float vegetableThreePlantedTime;
    float vegetableFourPlantedTime;
    
    int threshold;
    bool bLearnBakground;
    bool backgroundSubOn;
    bool debugMode;
    bool muted;

    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvColorImage colorImg;
    
    ofImage carrotImg;
    
    ofImage carrot;
    ofImage parsnip;
    ofImage radish;
    ofImage salad;
    ofImage leek;
    ofImage ground;
    ofImage indicator;
    
    ofVideoPlayer groundVideo;
    
    ofSoundPlayer plantSeedSound;
    ofSoundPlayer bgSound;

    vector<Vegetable *> vegetables;
    
    ofxKinect kinect;
    ofVideoGrabber vidGrabber;
    ofxFiducialTracker fidfinder;
};
