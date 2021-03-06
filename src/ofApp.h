#pragma once

#include "ofMain.h"

#include "ofxCv.h"
#include "ofxFiducialFinder.h"
#include "ofxFiducialTracker.h"
#include "ofxOpenCv.h"
#include "ofxXmlSettings.h"

#include "Vegetable.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void plantCarrot();
    
    int mappedFiducialXpos;
    int mappedFiducialYpos;
    
    int maxVegetablesOnScreen;
    
    int plantDelay;
    
    int cloudBigPos;
    int cloudSmallPos;
    
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
    
    ofImage cloudBig;
    ofImage cloudSmall;
    ofImage indicator;
    ofImage indicatorNone;
    
    ofVideoPlayer groundVideo;
    
    ofSoundPlayer plantSeedSound;
    ofSoundPlayer bgSound;

    vector<Vegetable *> vegetables;
    
    ofxXmlSettings settings;
    
    ofVideoGrabber vidGrabber;
    ofxFiducialTracker fidfinder;
};
