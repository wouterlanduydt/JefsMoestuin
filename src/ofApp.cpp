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
    
    ofSetFrameRate(60);
    
    carrot.load("images/carrot_sprite.png");
    tomato.load("images/tomato_sprite.png");
    radish.load("images/radish_sprite.png");
    parsnip.load("images/parsnip_sprite.png");
    salad.load("images/salad_sprite.png");
    
    ground.load("images/ground.png");
    ground.setAnchorPoint(0, ground.getHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    kinect.draw(0.0, 0.0);
    ofSetBackgroundColor(154, 231, 252);
    
    for (int i = 0; i < ofGetWidth(); i += ground.getWidth()) {
        ground.draw(i, ofGetHeight() );
    }
        
    for (int i = 0; i < vegetables.size(); i++) {
        vegetables[i]->draw();
    }

//    if (loopPosition < 3) {
//        loopPosition++;
//    } else if (loopPosition == 3) {
//        loopPosition = 0;
//    }
//
//     carrotSprite.drawSubsection(0, 0, carrotSprite.getWidth()/4, carrotSprite.getHeight(), carrotSprite.getWidth()/4 * loopPosition, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'c'){
        vegetables.push_back(new Vegetable(carrot, mouseX, ofGetElapsedTimeMillis(), 3));
    } else if (key == 't'){
        vegetables.push_back(new Vegetable(tomato, mouseX, ofGetElapsedTimeMillis(), 2));
    } else if (key == 's'){
        vegetables.push_back(new Vegetable(salad, mouseX, ofGetElapsedTimeMillis(), 3));
    } else if (key == 'r'){
        vegetables.push_back(new Vegetable(radish, mouseX, ofGetElapsedTimeMillis(), 2));
    } else if (key == 'p'){
        vegetables.push_back(new Vegetable(parsnip, mouseX, ofGetElapsedTimeMillis(), 5));
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
