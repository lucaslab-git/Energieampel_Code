#pragma once
#include "LED.h"

class Consumption_LED : public LED
{
private:
    bool debug_mode;

public:
    void set_state(bool new_state) override;
    void set_intensity(double new_intensity) override;
    void set_debug_mode(bool new_state);
};