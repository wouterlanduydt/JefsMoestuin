#include "ofApp.h"
#include <math.h>
#include "Vegetable.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    kinect.init();
    kinect.open();
    kinect.setCameraTiltAngle(0);

    if (kinect.isConnected()) {
        ofLog() << "kinect connected";
        
        colorImg.allocate(640, 480);
        grayImage.allocate(640, 480);
        grayBg.allocate(640, 480);
        grayDiff.allocate(640, 480);
        
    } else {
        ofLog() << "kinect not connected";
        
        vidGrabber.initGrabber(320, 240);
        colorImg.allocate(320, 240);
        grayImage.allocate(320, 240);
        grayBg.allocate(320, 240);
        grayDiff.allocate(320, 240);
    }
    
    threshold = 100;
    bLearnBakground = false;
    backgroundSubOn = false;
    
    ofSetFrameRate(24);
    
    indicator.load("images/indicator.png");
    
    carrotVideo.load("video/carrot.mov");
    leekVideo.load("video/leek.mov");
    radishVideo.load("video/radish.mov");
    parsnipVideo.load("video/parsnip.mov");
    saladVideo.load("video/salad.mov");
    
    ground.load("images/ground.png");
    ground.setAnchorPoint(0, 0);
    
    plantSeedSound.load("sounds/plant-seed.mp3");
    bgSound.load("sounds/bg-sound.mp3");
    bgSound.play();
    bgSound.setLoop(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    kinect.isConnected() ? kinect.update() : vidGrabber.update();
    
    carrotVideo.update();
    leekVideo.update();
    radishVideo.update();
    parsnipVideo.update();
    saladVideo.update();
    
    if (kinect.isFrameNew() && kinect.isConnected()){
        
        colorImg.setRoiFromPixels(kinect.getPixels().getData(), 640, 480);
        grayImage = colorImg;
        
        if (bLearnBakground == true){
            grayBg = grayImage;        // the = sign copys the pixels from grayImage into grayBg (operator overloading)
            bLearnBakground = false;
            backgroundSubOn = true;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        backgroundSubOn ? grayDiff.absDiff( grayBg, grayImage ) : grayDiff = grayImage;
        grayDiff.threshold(threshold);
        fidfinder.findFiducials( grayDiff );
        
    } else if (vidGrabber.isFrameNew()){
        
        colorImg.setRoiFromPixels(vidGrabber.getPixels().getData(), 320, 240);
        grayImage = colorImg;
        
        if (bLearnBakground == true){
            grayBg = grayImage;        // the = sign copys the pixels from grayImage into grayBg (operator overloading)
            bLearnBakground = false;
            backgroundSubOn = true;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        backgroundSubOn ? grayDiff.absDiff( grayBg, grayImage ) : grayDiff = grayImage;
        grayDiff.threshold(threshold);
        fidfinder.findFiducials( grayDiff );
    }
    
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
    
    for (int i = 0; i < ofGetWidth(); i += ground.getWidth()) {
        ground.draw(i, ofGetHeight() / 3);
    }
    
    for (int i = 0; i < vegetables.size(); i++) {
        vegetables[i]->draw();
    }
    
    if (debugMode && kinect.isConnected()) {
        colorImg.draw(0,0);
        grayDiff.draw(640,0);
    } else if (debugMode){
        colorImg.draw(0,0);
        grayDiff.draw(320,0);
    }
    
    //use this method for the FiducialTracker
    //to get fiducial info you can use the fiducial getter methods
    for (list<ofxFiducial>::iterator fiducial = fidfinder.fiducialsList.begin(); fiducial != fidfinder.fiducialsList.end(); fiducial++) {
        if (kinect.isConnected()) {
            mappedFiducialXpos = ofMap(fiducial->getX(), 0, 640, 0, ofGetWidth());
            mappedFiducialYpos = ofMap(fiducial->getY(), 0, 480, 0, ofGetHeight());
        } else {
            mappedFiducialXpos = ofMap(fiducial->getX(), 0, 320, 0, ofGetWidth());
            mappedFiducialYpos = ofMap(fiducial->getY(), 0, 240, 0, ofGetHeight());
        }
        
        if (debugMode == true) {
            fiducial->draw( 0, 0 );//draw fiducial
            fiducial->drawCorners( 0, 0 );//draw corners
            cout << "fiducial " << fiducial->getId() << " found at ( " << fiducial->getX() << "," << fiducial->getY() << " )" << endl;
        }
        
        indicator.setAnchorPoint(indicator.getWidth() / 2, 0);
        indicator.draw(mappedFiducialXpos, 10);
        
        if (fiducial->getId() == 0 && ofGetElapsedTimeMillis() > vegetableZeroPlantedTime + 5000){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable(carrotVideo, mappedFiducialXpos));
            vegetableZeroPlantedTime = ofGetElapsedTimeMillis();
            
        } else if (fiducial->getId() == 1 && ofGetElapsedTimeMillis() >= vegetableOnePlantedTime + 5000){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable(leekVideo, mappedFiducialXpos));
            vegetableOnePlantedTime = ofGetElapsedTimeMillis();
            
        } else if (fiducial->getId() == 2 && ofGetElapsedTimeMillis() >= vegetableTwoPlantedTime + 5000){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable(saladVideo, mappedFiducialXpos));
            vegetableTwoPlantedTime = ofGetElapsedTimeMillis();
            
        } else if (fiducial->getId() == 3 && ofGetElapsedTimeMillis() >= vegetableThreePlantedTime + 5000){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable(radishVideo, mappedFiducialXpos));
            vegetableThreePlantedTime = ofGetElapsedTimeMillis();
            
        } else if (fiducial->getId() == 4 && ofGetElapsedTimeMillis() >= vegetableFourPlantedTime + 5000){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable(parsnipVideo, mappedFiducialXpos));
            vegetableFourPlantedTime = ofGetElapsedTimeMillis();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == ' ' ) {
        bLearnBakground = true;
    } else if( key == '-' ) {
        threshold = max( 0, threshold-1 );
        ofLog() << threshold;
    } else if( key == '+' || key == '=' ) {
        threshold = min( 255, threshold+1 );
        ofLog() << threshold;
    } else if( key == 'b' ) {
        backgroundSubOn = false;
    } else if( key == 'd' ) {
        debugMode ? debugMode = false : debugMode = true;
    } else if( key == 'm' ) {
        muted ? muted = false : muted = true;
    } else if ( key == 'c' ) {
        vegetables.clear();
    }
}
