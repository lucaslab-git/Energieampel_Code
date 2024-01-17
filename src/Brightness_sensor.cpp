#include "Brightness_sensor.h"
#include "Arduino.h"

int Brightness_sensor::get_brightness()
{
    return (brightness);
}

void Brightness_sensor::read_sensor()
{
    brightness = analogRead(A0) / 1000;
}
