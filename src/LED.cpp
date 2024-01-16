#include "LED.h"

LED::LED()
{
    color = CRGB::White;
}

void LED::set_state(bool new_state)
{
    
    state = new_state;
}

void LED::set_intensity(double new_intensity)
{
    intensity = new_intensity;
}

bool LED::get_state() 
{
    return state;
}

int LED::get_intensity() 
{
    return intensity;
}

CRGB LED::get_color() 
{
    return color;
}
