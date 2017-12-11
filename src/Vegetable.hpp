//
//  Vegetable.hpp
//  jefsMoestuin
//
//  Created by Wouter Landuydt on 09/12/2017.
//

#ifndef Vegetable_hpp
#define Vegetable_hpp

#include <stdio.h>
#include "ofMain.h"

class Vegetable {
public:
    Vegetable(ofImage vegetableToDraw, int xPosToDraw, float plantedAt, int frames){
        image = vegetableToDraw;
        xPos = xPosToDraw;
        timePlanted = plantedAt;
        totalFrames = frames;
        spriteDivide = frames + 1;
    };
    
    void draw();
    void setup();
    
    int totalFrames;
    int spriteDivide;
    int loopPosition;
    
    ofImage image;
    int xPos;
    float timePlanted;
    float timeLastFrameIncrement;
};

#endif /* Vegetable_hpp */
