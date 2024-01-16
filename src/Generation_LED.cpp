// ConsumptionLED.cpp
#include "Generation_LED.h"

void Generation_LED::set_state(bool new_state)
{
    if (new_state)
    {
        color = CRGB(50 * intensity, 0 * intensity, 0 * intensity);
    }
    else
    {
        color = CRGB(0, 0, 0);
    }
}

void Generation_LED::set_intensity(double new_intensity)
{
    intensity = new_intensity;
}