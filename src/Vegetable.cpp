#include "Vegetable.hpp"

void Vegetable::draw() {
    video.draw(xPos, ofGetHeight() / 3, video.getWidth() * scale, video.getHeight() * scale);
}

void Vegetable::update() {
    video.update();
    if (video.getCurrentFrame() == 116) {
        pausedTime = ofGetElapsedTimeMillis() + (5);
    }

    if (ofGetElapsedTimeMillis() <= pausedTime) {
        video.setFrame(116);
    }
    video.setAnchorPoint((video.getWidth() * scale) / 2, (video.getHeight() * scale) / 2);
    video.setSpeed(growSpeed);
    video.setLoopState(OF_LOOP_NONE);
}

void Vegetable::remove() {
    video.close();
}
