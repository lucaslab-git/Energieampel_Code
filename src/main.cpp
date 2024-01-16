// main.cpp
#include <Arduino.h>
#include "FastLED.h"
#include "LED.h"
#include "Consumption_LED.h"
#include "Generation_LED.h"

#define num_leds 40
#define data_pin 2

int scaling_per_led = 250;

CRGB led_strip[num_leds];
Consumption_LED con_led[num_leds / 2];
Generation_LED gen_led[num_leds / 2];

void send_data()
{
  for (int i = 0; i < 20; i++)
  {
    led_strip[i] = con_led[i].get_color();
  }
  for (int i = 20; i < 40; i++)
  {
    led_strip[i] = gen_led[i - 20].get_color();
  }
  FastLED.show();
}

void updateleds(int consumption, int generation)
{
  for (int i = 0; i < 20; i++)
  {
    if (!con_led[i].get_state() && i < (consumption / scaling_per_led))
    {
      con_led[i].set_state(true);
    }
    else
    {
      con_led[i].set_state(false);
    }
  }

  for (int i = 0; i < 20; i++)
  {
    if (!gen_led[i].get_state() && i < (generation / scaling_per_led))
    {
      gen_led[i].set_state(true);
    }
    else
    {
      gen_led[i].set_state(false);
    }
  }

  send_data();
}

void setup()
{
  for (int i = 0; i < 20; i++)
  {
    con_led[i].set_debug_mode(true);
  }

  Serial.begin(9600);

  FastLED.addLeds<WS2812B, data_pin, RGB>(led_strip, num_leds);

  // simulation von wifi connection für debug led
  for (int i = 0; i < 20; i++)
  {
    led_strip[i] = con_led[i].get_color();
    FastLED.show();
    delay(200);
  }

  for (int i = 0; i < 20; i++)
  {
    con_led[i].set_debug_mode(false);
  }

  Serial.println("End");
  updateleds(1000, 1250);
}

void loop()
{
}