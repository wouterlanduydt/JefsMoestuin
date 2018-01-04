#include "Vegetable.hpp"

void Vegetable::draw() {
    video.draw(xPos, ofGetHeight() / 3, video.getWidth() * scale, video.getHeight() * scale);
    
    if (video.getCurrentFrame() == 116) {
        pausedTime = ofGetElapsedTimeMillis() + (60000*5);
    }
    
    if (ofGetElapsedTimeMillis() <= pausedTime) {
        video.setFrame(116);
    }
}

void Vegetable::update() {
    video.update();
    video.setAnchorPoint((video.getWidth() * scale) / 2, (video.getHeight() * scale) / 2);
    video.setSpeed(growSpeed);
    video.setLoopState(OF_LOOP_NONE);
}

void Vegetable::remove() {
    video.close();
}
