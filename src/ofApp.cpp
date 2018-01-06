#include "ofApp.h"
#include <math.h>
#include "Vegetable.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    vidGrabber.listDevices().size() > 1 ? vidGrabber.setDeviceID(1) : vidGrabber.setDeviceID(0);
    
    vidGrabber.initGrabber(640, 480);
    colorImg.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
    grayImage.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
    grayBg.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
    grayDiff.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
    
    threshold = 115;
    bLearnBakground = false;
    backgroundSubOn = false;
    plantDelay = 10000;
    
    ofSetFrameRate(24);
    maxVegetablesOnScreen = 35;
    
    indicator.load("images/indicator.png");
    indicatorNone.load("images/indicator_none.png");
    cloudBig.load("images/cloud-big.png");
    cloudSmall.load("images/cloud-small.png");
    
    cloudBigPos = ofRandom(0, ofGetWidth());
    cloudSmallPos = ofRandom(0, ofGetWidth());
    
    groundVideo.load("videos/ground.mov");
    groundVideo.play();
    
    plantSeedSound.load("sounds/plant-seed.mp3");
    bgSound.load("sounds/bg-sound.mp3");
    bgSound.play();
    bgSound.setLoop(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    groundVideo.update();
    
    cloudBigPos += 1;
    cloudSmallPos -= 1;
    
    for (int i = 0; i < vegetables.size(); i++) {
        vegetables[i]->update();
    }
    
    colorImg.setRoiFromPixels(vidGrabber.getPixels().getData(), colorImg.getWidth(), colorImg.getHeight());
    
    grayImage = colorImg;
    
    if (bLearnBakground) {
        grayBg = grayImage;
        bLearnBakground = false;
        backgroundSubOn = true;
    }
    
    // take the abs value of the difference between background and incoming and then threshold:
    backgroundSubOn ? grayDiff.absDiff(grayBg, grayImage) : grayDiff = grayImage;
    grayDiff.threshold(threshold);
    fidfinder.findFiducials(grayDiff);
    
    if (muted == true) {
        bgSound.setVolume(0);
        plantSeedSound.setVolume(0);
    } else {
        bgSound.setVolume(1);
        plantSeedSound.setVolume(1);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofGetHours() <= 17 ? ofSetBackgroundColor(240, 247, 246) : ofSetBackgroundColor(21, 48, 36);
    
    for (int i = 0; i < ofGetWidth(); i += groundVideo.getWidth()) {
        groundVideo.draw(i, ofGetHeight() / 3);
    }
    
    if (vegetables.size() > maxVegetablesOnScreen) {
        vegetables[0]->remove();
        vegetables.erase(vegetables.begin());
    }
    
    for (int i = 0; i < vegetables.size(); i++) {
        vegetables[i]->draw();
        
        if (vegetables[i]->scale <= 0) {
            vegetables[i]->remove();
            vegetables.erase(vegetables.begin());
        }
    }
    
    cloudBig.draw(cloudBigPos, -10);
    cloudSmall.draw(cloudSmallPos, cloudBig.getHeight());
    
    if (debugMode) {
        colorImg.draw(0, 0, colorImg.getWidth(), colorImg.getHeight());
        grayDiff.draw(grayDiff.getWidth(), 0, grayDiff.getWidth(), grayDiff.getHeight());
        ofDrawBitmapString("VEGETABLES ON SCREEN: " + ofToString(vegetables.size()), 10, ofGetHeight() - 40);
        ofDrawBitmapString("THRESHOLD: " + ofToString(threshold), 10, ofGetHeight() - 20);
    }
    
    if (cloudBigPos > ofGetWidth() ) { cloudBigPos = - cloudBig.getWidth(); }
    if (cloudSmallPos < - cloudSmall.getWidth() ) { cloudSmallPos = ofGetWidth(); }
    
    //use this method for the FiducialTracker
    //to get fiducial info you can use the fiducial getter methods
    for (list<ofxFiducial>::iterator fiducial = fidfinder.fiducialsList.begin(); fiducial != fidfinder.fiducialsList.end(); fiducial++) {
        
        mappedFiducialXpos = ofMap(fiducial->getX(), 0, colorImg.getWidth(), -fiducial->getRootSize(), ofGetWidth() + fiducial->getRootSize());
        mappedFiducialYpos = ofMap(fiducial->getY(), 0, colorImg.getHeight(), -fiducial->getRootSize(), ofGetHeight() + -fiducial->getRootSize());
        
        // first fiducial might have a negative X pos first iteration - ignore it
        if (mappedFiducialXpos < 0) { continue; }
        
        if (debugMode) {
            fiducial->draw(0, 0);//draw fiducial
            fiducial->drawCorners(0, 0);//draw corners
            ofLog() << "FID " << fiducial->getId() << " found at (" << fiducial->getX() << ", " << fiducial->getY() << ")";
        }
        
        for (int j = -20; j < 20; j++) {
            for (int i = 0; i < vegetables.size(); i++) {
                if (vegetables[i]->xPos + j == mappedFiducialXpos) {
                    indicatorNone.draw(mappedFiducialXpos, 10);
                    return;
                }
            }
        }
        
        indicator.setAnchorPoint(indicator.getWidth() / 2, 0);
        indicator.draw(mappedFiducialXpos, 10);
        
        if (fiducial->getId() == 0 && ofGetElapsedTimeMillis() >= vegetableZeroPlantedTime){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable("parsnip", mappedFiducialXpos));
            vegetableZeroPlantedTime = ofGetElapsedTimeMillis() + plantDelay;
        } else if (fiducial->getId() == 1 && ofGetElapsedTimeMillis() >= vegetableOnePlantedTime) {
            plantSeedSound.play();
            vegetables.push_back(new Vegetable("leek", mappedFiducialXpos));
            vegetableOnePlantedTime = ofGetElapsedTimeMillis() + plantDelay;
        } else if (fiducial->getId() == 2 && ofGetElapsedTimeMillis() >= vegetableTwoPlantedTime) {
            plantSeedSound.play();
            vegetables.push_back(new Vegetable("salad", mappedFiducialXpos));
            vegetableTwoPlantedTime = ofGetElapsedTimeMillis() + plantDelay;
        } else if (fiducial->getId() == 3 && ofGetElapsedTimeMillis() >= vegetableThreePlantedTime) {
            plantSeedSound.play();
            vegetables.push_back(new Vegetable("carrot", mappedFiducialXpos));
            vegetableThreePlantedTime = ofGetElapsedTimeMillis() + plantDelay;
        } else if (fiducial->getId() == 4 && ofGetElapsedTimeMillis() >= vegetableFourPlantedTime) {
            plantSeedSound.play();
            vegetables.push_back(new Vegetable("radish", mappedFiducialXpos));
            vegetableFourPlantedTime = ofGetElapsedTimeMillis() + plantDelay;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == ' ' ) {
        bLearnBakground = true;
    } else if( key == '-' ) {
        threshold = max( 0, threshold-1 );
    } else if( key == '+' || key == '=' ) {
        threshold = min( 255, threshold+1 );
    } else if( key == 'b' ) {
        backgroundSubOn = false;
    } else if( key == 'd' ) {
        debugMode ? debugMode = false : debugMode = true;
    } else if( key == 'm' ) {
        muted ? muted = false : muted = true;
    } else if ( key == 'c' ) {
        for (int i = 0; i < vegetables.size(); i++) {
            vegetables[i]->remove();
            vegetables.erase(vegetables.begin() + i);
        }
        vegetables.clear();
    }
}
