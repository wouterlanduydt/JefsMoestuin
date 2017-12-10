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
        void draw();

    ofImage image;
    int xPos;
    
    Vegetable(ofImage vegetableToDraw, int xPosToDraw){
        image = vegetableToDraw;
        xPos = xPosToDraw;
    };
};

#endif /* Vegetable_hpp */
