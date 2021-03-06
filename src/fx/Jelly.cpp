#include "Jelly.h"

Jelly::Jelly(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    for (int i = 0; i < ITEMS; i++) {
        items[i].setup(strip);
    }
}

void Jelly::reset() {
    clear(strip);
    for (int i = 0; i < ITEMS; i++) {
        uint8_t size = random8(2, 5);
        items[i].reset()
            .setColor(ColorFromPalette(PALETTE, random8()))
            .setElasticConstant(4)
            .setCriticalDamping()
            .setFixedPointPosition(strip->random())
            .setVelocity(10)
            .setRange(-size, size)
            .setMirror(false)
            .setShowWhenStable(true);
    }
    moveTimer.reset();
    fadeTimer.reset();
}

void Jelly::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(FADE_RATE);
    }

    if (audioChannel->trigger(2)) {
        if (moveTimer.isElapsed()) {
            for (int i = 0; i < ITEMS; i++) {
                items[i].setFixedPointPosition(strip->randomExclude(items[i].getPosition(), 5));
            }
        }
    }
    
    for (int i = 0; i < ITEMS; i++) {
        items[i].setElasticConstant(5 + 100 * state->parabolicFxSpeed);
        items[i].setCriticalDamping();
        items[i].loop();
    }
}
