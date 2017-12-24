#pragma once

#include "ofMain.h"
#include "ofxKinect.h"

#include "Vegetable.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    ofImage carrot;
    ofImage parsnip;
    ofImage radish;
    ofImage salad;
    ofImage tomato;
    ofImage ground;
    
    ofSoundPlayer plantSeedSound;
    ofSoundPlayer bgSound;
    
    vector<Vegetable *> vegetables;
    
    ofxKinect kinect;
};
