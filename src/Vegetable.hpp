#ifndef Vegetable_hpp
#define Vegetable_hpp

#include <stdio.h>
#include "ofMain.h"

class Vegetable {
public:
    Vegetable(string vegetableToDraw, int xPosToDraw){
        video.load("videos/" + vegetableToDraw + ".mov");

        xPos = xPosToDraw;
        growSpeed = ofRandom(.05, .1);
        scale = ofRandom(.7, 1);
    };
        
    void draw();
    void setup();
    void update();
    void remove();
    
    float growSpeed;
    float scale;
    
    ofVideoPlayer video;
    int xPos;
    int pausedTime;
};

#endif /* Vegetable_hpp */
