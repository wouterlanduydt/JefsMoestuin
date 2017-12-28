//
//  Vegetable.cpp
//  jefsMoestuin
//
//  Created by Wouter Landuydt on 09/12/2017.
//

#include "Vegetable.hpp"

void Vegetable::draw() {
    video.setAnchorPoint(video.getWidth()*scale / 2, video.getHeight()*scale / 2);
    video.draw(xPos, ofGetHeight() / 3, video.getWidth()*scale, video.getHeight()*scale);
    video.setSpeed(growSpeed);
    video.play();
    video.setLoopState(OF_LOOP_NONE);
}
