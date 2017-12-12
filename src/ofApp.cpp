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
    ground.setAnchorPoint(0, 70);
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // kinect.draw(0.0, 0.0);
    
    // make the sky darker after 17:00.
    // TODO: Look for a way to animate the color values.
    if(ofGetHours() >= 17) {
        ofSetBackgroundColor(50, 120, 150);
    } else {
        ofSetBackgroundColor(196, 236, 255);
    }
    
    for (int i = 0; i < ofGetWidth(); i += ground.getWidth()) {
        ground.draw(i, ofGetHeight() / 3);
    }
    
    for (int i = 0; i < vegetables.size(); i++) {
        vegetables[i]->draw();
    }
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
void ofApp::mousePressed(int x, int y, int button){
    if (x >= ofGetWidth() - 50 && y >= ofGetHeight() - 50) {
        vegetables.clear();
    }
}
