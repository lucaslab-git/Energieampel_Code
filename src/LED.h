// LED.h
#pragma once
#include "FastLED.h"

class LED
{
protected:
    bool state;
    double intensity = 1;
    CRGB color;

public:
    LED();
    virtual void set_state(bool new_state);
    virtual void set_intensity(double new_intensity);
    bool get_state();
    int get_intensity();
    CRGB get_color();
};