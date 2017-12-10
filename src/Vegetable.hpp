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
    Vegetable(ofImage vegetableToDraw, int xPosToDraw, float plantedAt){
        image = vegetableToDraw;
        xPos = xPosToDraw;
        timePlanted = plantedAt;
    };
    
    void draw();
    
    ofImage image;
    int xPos;
    float timePlanted;
};

#endif /* Vegetable_hpp */
