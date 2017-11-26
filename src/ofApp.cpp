#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // BUG: flicker
    ofSetBackgroundAuto(false);
    
    // Load image and set anchorpoint
    testPlant.load("images/testplant.png");
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
    for(int i = 0; i < ofGetScreenWidth(); i += ground.getWidth()){
        ground.draw(i, ofGetScreenHeight() );
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
    // ofSleepMillis(delay);
    
    // draws plant at pressed position
    testPlant.draw(x, y);
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
