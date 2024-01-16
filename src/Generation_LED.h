#pragma once
#include "LED.h"

class Generation_LED : public LED
{
public:
    void set_state(bool new_state) override;
    void set_intensity(double new_intensity) override;
};