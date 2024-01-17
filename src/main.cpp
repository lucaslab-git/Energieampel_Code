// main.cpp
#include <Arduino.h>
#include "FastLED.h"
#include "LED.h"
#include "Consumption_LED.h"
#include "Generation_LED.h"
#include "ESPAsyncWebServer.h"
#include <WiFi.h>

const char *ssid = "demospot";
const char *password = "energieampel";

#define num_leds 40
#define data_pin 2

int scaling_per_led = 250;

CRGB led_strip[num_leds];
Consumption_LED con_led[num_leds / 2];
Generation_LED gen_led[num_leds / 2];
AsyncWebServer server(80);

void send_data()
{
  for (int i = 19; i > 0; i--)
  {
    led_strip[i] = CRGB(0, 0, 0);
    led_strip[i + 20] = CRGB(0, 0, 0);
    delay(85);
    FastLED.show();
  }
  for (int i = 0; i < 20; i++)
  {
    led_strip[i] = con_led[i].get_color();
    led_strip[i + 20] = gen_led[i].get_color();
    delay(85);
    FastLED.show();
  }
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

void set_url()
{

  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request) // url/update?con?gen
            {
      Serial.println("update");
      AsyncWebParameter* con = request->getParam(0);
      AsyncWebParameter* gen = request->getParam(1);
      Serial.println(con->value().toInt());
      Serial.println(gen->value().toInt());
      updateleds(con->value().toInt(), gen->value().toInt());
      request->send(200, "text/plain", "message received"); });
}

void setup()
{
  FastLED.addLeds<WS2812B, data_pin, RGB>(led_strip, num_leds);
  for (int i = 0; i < 20; i++)
  {
    con_led[i].set_debug_mode(true);
  }

  Serial.begin(9600);

  Serial.println("Start");

  int i = 0;

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(i);
    i++;
    led_strip[i] = con_led[i].get_color();
    FastLED.show();
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
  led_strip[19] = con_led[19].get_color();
  FastLED.show();

  for (int i = 0; i < 20; i++)
  {
    con_led[i].set_debug_mode(false);
  }

  Serial.println("End");
  set_url();
  server.begin();
}

void loop()
{
}