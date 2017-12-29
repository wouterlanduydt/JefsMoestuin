#ifndef Vegetable_hpp
#define Vegetable_hpp

#include <stdio.h>
#include "ofMain.h"

class Vegetable {
public:
    Vegetable(ofVideoPlayer vegetableToDraw, int xPosToDraw){
        video = vegetableToDraw;
        xPos = xPosToDraw;
        timePlanted = ofGetElapsedTimeMillis();
        growSpeed = ofRandom(.2, .3);
        scale = ofRandom(.5, 1);
    };
    
    void draw();
    void setup();
    
    float test;
    float growSpeed;
    float scale;
    
    ofVideoPlayer video;
    int xPos;
    float timePlanted;
};

#endif /* Vegetable_hpp */
