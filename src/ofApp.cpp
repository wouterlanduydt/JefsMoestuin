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
    carrot.load("images/carrot_sprite.png");
    tomato.load("images/tomato_sprite.png");
    radish.load("images/radish_sprite.png");
    parsnip.load("images/parsnip_sprite.png");
    salad.load("images/salad_sprite.png");

    testVideo.load("video/videoTest.mov");
    testVideo.setLoopState(OF_LOOP_NONE);
    
    ground.load("images/ground.png");
    ground.setAnchorPoint(0, 70);
    
    plantSeedSound.load("sounds/plant-seed.mp3");
    bgSound.load("sounds/bg-sound.mp3");
    bgSound.play();
    bgSound.setLoop(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (kinect.isConnected()) {
        kinect.update();
    } else {
       vidGrabber.update();
    }
    testVideo.update();
    
    if (kinect.isFrameNew() && kinect.isConnected()){
        
        colorImg.setRoiFromPixels(kinect.getPixels().getData(), 640, 480);
        grayImage = colorImg;
        
        if (bLearnBakground == true){
            grayBg = grayImage;        // the = sign copys the pixels from grayImage into grayBg (operator overloading)
            bLearnBakground = false;
            backgroundSubOn = true;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        if (backgroundSubOn) {
            grayDiff.absDiff( grayBg, grayImage );
        } else {
            grayDiff = grayImage;
        }
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
        if (backgroundSubOn) {
            grayDiff.absDiff( grayBg, grayImage );
        } else {
            grayDiff = grayImage;
        }
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
    // make the sky darker after 17:00.
    // TODO: Look for a way to animate the color values.
    if(ofGetHours() <= 17) {
        ofSetBackgroundColor(240, 247, 246);
    } else {
        ofSetBackgroundColor(21, 48, 36);
    }
    
    for (int i = 0; i < ofGetWidth(); i += ground.getWidth()) {
        ground.draw(i, ofGetHeight() / 3);
    }
    
    for (int i = 0; i < vegetables.size(); i++) {
        vegetables[i]->draw();
    }
    
    if (debugMode == true && kinect.isConnected()) {
        colorImg.draw(0,0);
        grayDiff.draw(640,0);
    } else if (debugMode == true){
        colorImg.draw(0,0);
        grayDiff.draw(320,0);
    }
    testVideo.draw(10, 100, 70, 120);
    testVideo.setSpeed(.2);
    testVideo.play();
    
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
        
        if (fiducial->getId()) {
            indicator.setAnchorPoint(indicator.getWidth() / 2, indicator.getHeight() / 2);
            indicator.draw(mappedFiducialXpos, 10);
        }
        
        if (fiducial->getId() == 0 && ofGetElapsedTimeMillis() > vegetableZeroPlantedTime + 5000){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable(carrot, mappedFiducialXpos, ofGetElapsedTimeMillis(), 0, ofRandom(1000, 3000)));
            vegetableZeroPlantedTime = ofGetElapsedTimeMillis();
            
        } else if (fiducial->getId() == 1 && ofGetElapsedTimeMillis() >= vegetableOnePlantedTime + 5000){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable(leek, mappedFiducialXpos, ofGetElapsedTimeMillis(), 0, ofRandom(1000, 3000)));
            vegetableOnePlantedTime = ofGetElapsedTimeMillis();
            
        } else if (fiducial->getId() == 2 && ofGetElapsedTimeMillis() >= vegetableTwoPlantedTime + 5000){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable(salad, mappedFiducialXpos, ofGetElapsedTimeMillis(), 0, ofRandom(1000, 3000)));
            vegetableTwoPlantedTime = ofGetElapsedTimeMillis();
            
        } else if (fiducial->getId() == 3 && ofGetElapsedTimeMillis() >= vegetableThreePlantedTime + 5000){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable(radish, mappedFiducialXpos, ofGetElapsedTimeMillis(), 0, ofRandom(1000, 3000)));
            vegetableThreePlantedTime = ofGetElapsedTimeMillis();
            
        } else if (fiducial->getId() == 4 && ofGetElapsedTimeMillis() >= vegetableFourPlantedTime + 5000){
            plantSeedSound.play();
            vegetables.push_back(new Vegetable(parsnip, mappedFiducialXpos, ofGetElapsedTimeMillis(), 0, ofRandom(1000, 3000)));
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
        if (debugMode == false) {
            ofLog() << "debug mode ON";
            debugMode = true;
        } else if (debugMode == true) {
            ofLog() << "debug mode OFF";
            debugMode = false;
        }
    } else if( key == 'm' ) {
        if (muted == false) {
            muted = true;
        } else if (muted == true) {
            muted = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (x >= ofGetWidth() - 50 && y >= ofGetHeight() - 50) {
        vegetables.clear();
    }
}
