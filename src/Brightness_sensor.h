#pragma once

class Brightness_sensor
{
private:
    double brightness;

public:
    int get_brightness();
    void read_sensor();
};