//
//  Vegetable.cpp
//  jefsMoestuin
//
//  Created by Wouter Landuydt on 09/12/2017.
//

#include "Vegetable.hpp"

void Vegetable::draw() {
    if (loopPosition < totalFrames) {
        if (ofGetElapsedTimeMillis() > timePlanted + growSpeed) {
            loopPosition++;
            timePlanted = ofGetElapsedTimeMillis();
        }
    }
    image.setAnchorPoint(image.getWidth() / spriteDivide / 2, image.getHeight() / 3);
    image.drawSubsection(xPos, ofGetHeight() / 3, image.getWidth() / spriteDivide, image.getHeight(), image.getWidth() / spriteDivide * loopPosition, 0);
}
