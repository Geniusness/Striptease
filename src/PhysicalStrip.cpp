#include "PhysicalStrip.h"

PhysicalStrip::PhysicalStrip(CRGBSet &leds, uint16_t density) {
    this->leds = &leds;
    this->density = density;
}

uint16_t PhysicalStrip::size() {
    return leds->size();
}

uint16_t PhysicalStrip::first() {
    return 0;
}

uint16_t PhysicalStrip::center() {
    return size() / 2;    
}

uint16_t PhysicalStrip::last() {
    return size() - 1;    
}

uint16_t PhysicalStrip::random() {
    return random16(size());
}

uint16_t PhysicalStrip::randomExclude(uint16_t excludeIndex, uint16_t excludeCount) {
    return (excludeIndex + excludeCount + random16(size() - 2 * excludeCount)) % size();
}

uint16_t PhysicalStrip::randomInRange(float from, float to) {
    return random16(from * size(), to * size());
}

uint16_t PhysicalStrip::fromNormalizedPosition(float normalizedPosition, uint16_t excludeCount) {
    return int(normalizedPosition * (last() - excludeCount));
}

bool PhysicalStrip::isInRange(int16_t index) {
    return index >= 0 && index < size();
}

uint16_t PhysicalStrip::limitToRange(int16_t index) {
    return max(min(index, last()), 0);
}

void PhysicalStrip::off() {
    *leds = CRGB::Black;
}

void PhysicalStrip::rainbow(uint8_t initialHue) {
    rainbow(initialHue, max(255 / size(), 1));
}

void PhysicalStrip::rainbow(uint8_t initialHue, uint8_t deltaHue) {
    leds->fill_rainbow(initialHue, deltaHue);
}

void PhysicalStrip::fade(uint8_t amount) {
    leds->fadeToBlackBy(amount);
}

void PhysicalStrip::blur(uint8_t amount) {
    leds->blur1d(amount);
}

CRGB PhysicalStrip::shiftUp(CRGB in) {
    CRGB out = (*leds)[last()];
    for (int i = last(); i > 0 ; i--) {
        (*leds)[i] = (*leds)[i - 1];
    }
    (*leds)[first()] = in;
    return out;
}

CRGB PhysicalStrip::shiftDown(CRGB in) {
    CRGB out = (*leds)[first()];
    for (int i = 0; i < last(); i++) {
        (*leds)[i] = (*leds)[i + 1];
    }
    (*leds)[last()] = in;
    return out;
}

void PhysicalStrip::paint(CRGB color, bool add) {
    if (add) {
        *leds |= color;
    } else {
        *leds = color;
    }
}

bool PhysicalStrip::paint(int16_t index, CRGB color, bool add) {
    if (isInRange(index)) {
        if (add) {
            (*leds)[index] |= color;
        } else {
            (*leds)[index] = color;
        }
        return true;
    }
    return false;
}

bool PhysicalStrip::paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    int16_t posMin = min(indexFrom, indexTo);
    int16_t posMax = max(indexFrom, indexTo);
    if (isInRange(posMin) || isInRange(posMax)) {
        if (add) {
            (*leds)(limitToRange(posMin), limitToRange(posMax)) |= color;
        } else {
            (*leds)(limitToRange(posMin), limitToRange(posMax)) = color;
        }
        return true;
    }
    return false;
}

bool PhysicalStrip::paintNormalized(float position, CRGB color, bool add) {
    return paint(fromNormalizedPosition(position), color, add);
}

bool PhysicalStrip::paintNormalized(float positionFrom, float positionTo, CRGB color, bool add) {
    return paint(fromNormalizedPosition(positionFrom), fromNormalizedPosition(positionTo), color, add);
}

bool PhysicalStrip::paintNormalizedSize(float positionFrom, uint16_t size, CRGB color, bool add) {
    uint16_t start = fromNormalizedPosition(positionFrom, size);
    return paint(start, start + size, color, add);
}

bool PhysicalStrip::paintRandomPos(uint16_t length, CRGB color, bool add) {
    uint16_t pos = random16(size() - length);
    return paint(pos, pos + length, color, add);
}
