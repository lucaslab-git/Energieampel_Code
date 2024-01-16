// ConsumptionLED.cpp
#include "Consumption_LED.h"

void Consumption_LED::set_state(bool new_state)
{
    if (new_state)
    {
        color = CRGB(0 * intensity, 50 * intensity, 0 * intensity);
    }
    else
    {
        color = CRGB(0, 0, 0);
    }
}

void Consumption_LED::set_intensity(double new_intensity)
{
    intensity = new_intensity;
}

void Consumption_LED::set_debug_mode(bool new_state)
{
    if (new_state)
    {
        color = CRGB(0, 0, 50);
    }
    else
    {
        color = CRGB(0, 0, 0);
    }
}