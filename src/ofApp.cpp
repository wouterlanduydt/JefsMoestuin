#include "ofApp.h"
#include <math.h>
#include "Vegetable.hpp"

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
    
    carrot.load("images/carrot_sprite-ae.png");
    tomato.load("images/tomato_sprite.png");
    radish.load("images/radish_sprite.png");
    parsnip.load("images/parsnip_sprite.png");
    salad.load("images/salad_sprite.png");
    
    ground.load("images/ground.png");
    ground.setAnchorPoint(0, 70);
    
    plantSeedSound.load("sounds/plant-seed.mp3");
    bgSound.load("sounds/bg-sound.mp3");
    bgSound.play();
    bgSound.setLoop(true);
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
        plantSeedSound.play();
        vegetables.push_back(new Vegetable(carrot, mouseX, ofGetElapsedTimeMillis(), 298, ofRandom(1000, 3000)));
    } else if (key == 't'){
        plantSeedSound.play();
        vegetables.push_back(new Vegetable(tomato, mouseX, ofGetElapsedTimeMillis(), 2, ofRandom(1000, 3000)));
    } else if (key == 's'){
        plantSeedSound.play();
        vegetables.push_back(new Vegetable(salad, mouseX, ofGetElapsedTimeMillis(), 3, ofRandom(1000, 3000)));
    } else if (key == 'r'){
        plantSeedSound.play();
        vegetables.push_back(new Vegetable(radish, mouseX, ofGetElapsedTimeMillis(), 2, ofRandom(1000, 3000)));
    } else if (key == 'p'){
        plantSeedSound.play();
        vegetables.push_back(new Vegetable(parsnip, mouseX, ofGetElapsedTimeMillis(), 5, ofRandom(1000, 3000)));
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (x >= ofGetWidth() - 50 && y >= ofGetHeight() - 50) {
        vegetables.clear();
    }
}
