#include "ofApp.h"
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(154, 231, 252);
    
    kinect.init(true);
    kinect.open();
    kinect.setCameraTiltAngle(10);
    if(kinect.isConnected()) {
        ofLog() << "kinect connected";
    }
    
    ofSetFrameRate(10);
    
    carrot.load("images/carrot.png");
    tomato.load("images/tomato.png");
    radish.load("images/radish.png");
    parsnip.load("images/parsnip.png");
    salad.load("images/salad.png");
    testSprite.load("images/testSprite.png");
    ground.load("images/ground.png");
    ground.setAnchorPoint(0, ground.getHeight());
    
    loopPosition = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // kinect.draw(0.0, 0.0);
    ofSetBackgroundColor(154, 231, 252);
    
    for (int i = 0; i < ofGetWidth(); i += ground.getWidth()) {
        ground.draw(i, ofGetHeight() );
    }
        
    for (int i = 0; i < vegetables.size(); i++) {
        vegetables[i]->draw();
    }
    
    if (loopPosition < 6) {
        loopPosition++;
    } else if (loopPosition > 5) {
        loopPosition = 0;
    }

    // testSprite.drawSubsection(400, 200, 108, 140, 108 * loopPosition, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'c'){
        vegetables.push_back(new Vegetable(carrot, mouseX));
    } else if (key == 't'){
        vegetables.push_back(new Vegetable(tomato, mouseX));
    } else if (key == 's'){
        vegetables.push_back(new Vegetable(salad, mouseX));
    } else if (key == 'r'){
        vegetables.push_back(new Vegetable(radish, mouseX));
    } else if (key == 'p'){
        vegetables.push_back(new Vegetable(parsnip, mouseX));
    }
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
