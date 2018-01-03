#ifndef Vegetable_hpp
#define Vegetable_hpp

#include <stdio.h>
#include "ofMain.h"

class Vegetable {
public:
    Vegetable(string vegetableToDraw, int xPosToDraw){
        video.load("videos/" + vegetableToDraw + ".mov");

        xPos = xPosToDraw;
        timePlanted = ofGetElapsedTimeMillis();
        growSpeed = ofRandom(.2, .3);
        scale = ofRandom(.5, 1);
    };
        
    void draw();
    void setup();
    void update();
    void remove();
    
    float test;
    float growSpeed;
    float scale;
    
    ofVideoPlayer video;
    int xPos;
    float timePlanted;
};

#endif /* Vegetable_hpp */
