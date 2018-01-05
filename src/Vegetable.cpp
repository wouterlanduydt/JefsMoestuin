#include "Vegetable.hpp"

void Vegetable::draw() {
    video.draw(xPos, ofGetHeight() / 3, video.getWidth() * scale, video.getHeight() * scale);
}

void Vegetable::update() {

    if (video.getCurrentFrame() == 115) {
        video.update();
        pausedTime = ofGetElapsedTimeMillis() + (5000);
    }

    if (ofGetElapsedTimeMillis() >= pausedTime && scale >= 0) {
        video.update();
        if (video.getCurrentFrame() == 116) {
            scale-=.01;
        }
        ofLog() << "playing at " << video.getCurrentFrame();
    } else if (scale <= 0) {
        video.close();
    }
    
    video.setAnchorPoint((video.getWidth() * scale) / 2, (video.getHeight() * scale) / 2);
    video.setSpeed(growSpeed);
    video.setLoopState(OF_LOOP_NONE);
}

void Vegetable::remove() {
    video.close();
}
