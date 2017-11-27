#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // BUG: flicker
    ofSetBackgroundColor(154, 231, 252);
    
    // Load image and set anchorpoint
    testPlant.load("images/carrot.png");
    testPlant.setAnchorPoint(testPlant.getWidth()/2, testPlant.getHeight()/2);
    
    ground.load("images/ground.png");
    ground.setAnchorPoint(0, ground.getHeight());
    
    // set delay after click
    delay = 3000;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(154, 231, 252);
    
    for(int i = 0; i < ofGetWidth(); i += ground.getWidth()){
        ground.draw(i, ofGetHeight() );
    }
    // for every object in Vector carrots, draw a carrot
    for (int i = 0; i < carrots.size(); i++) {
        testPlant.draw(carrots[i]);
        ofLog() << carrots[i];
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // Log clicked x and y position.
    ofLog() << "xpos: " << x << " ypos: " << y;
    
    // Set delay before drawing plant
//    ofSleepMillis(delay);
    
    // draws plant at pressed position
    carrots.push_back(ofPoint(x, ofGetHeight() - ground.getHeight()));
    
    // Timestamp plant created
    plantedCarrot = ofGetTimestampString();
    ofLog() << plantedCarrot;
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
