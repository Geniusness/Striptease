#ifndef Strip_h
#define Strip_h

#include <FastLED.h>

class Strip {
    public:
        virtual bool isInRange(int16_t index);
        virtual uint16_t limitToRange(int16_t index);
        virtual uint16_t size();
        virtual uint16_t first();
        virtual uint16_t center();
        virtual uint16_t last();
        virtual uint16_t random();
        virtual uint16_t randomExclude(uint16_t excludeIndex, uint16_t excludeCount = 0);
        virtual uint16_t randomInRange(float from, float to);
        virtual uint16_t fromNormalizedPosition(float normalizedPosition, uint16_t excludeCount = 0);

        virtual void off();
        virtual void rainbow(uint8_t initialHue);
        virtual void rainbow(uint8_t initialHue, uint8_t deltaHue);
        virtual void fade(uint8_t amount);
        virtual void blur(uint8_t amount);
        virtual CRGB shiftUp(CRGB in = CRGB::Black);
        virtual CRGB shiftDown(CRGB in = CRGB::Black);
        virtual void paint(CRGB color, bool add = false);
        virtual bool paint(int16_t index, CRGB color, bool add = true);
        virtual bool paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add = true);
        virtual bool paintNormalized(float position, CRGB color, bool add = true);
        virtual bool paintNormalized(float positionFrom, float positionTo, CRGB color, bool add = true);
        virtual bool paintNormalizedSize(float positionFrom, uint16_t size, CRGB color, bool add = true);
        virtual bool paintRandomPos(uint16_t length, CRGB color, bool add = true);
};

#endif
