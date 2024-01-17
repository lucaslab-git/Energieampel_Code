// main.cpp
#include <Arduino.h>
#include "FastLED.h"
#include "LED.h"
#include "Consumption_LED.h"
#include "Generation_LED.h"
#include "ESPAsyncWebServer.h"
#include "Brightness_sensor.h"
#include <WiFi.h>

const char *ssid = "Villa_Kunterbunt";
const char *password = "956795,Luca";

#define num_leds 40
#define data_pin 2

int scaling_per_led = 250;

CRGB led_strip[num_leds];
Consumption_LED con_led[num_leds / 2];
Generation_LED gen_led[num_leds / 2];
Brightness_sensor brightness_sensor; // konstuktor A0
AsyncWebServer server(80);

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
  brightness_sensor.read_sensor();
  for (int i = 0; i < 20; i++)
  {
    con_led[i].set_intensity(brightness_sensor.get_brightness());
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
    gen_led[i].set_intensity(brightness_sensor.get_brightness());
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

      AsyncWebParameter* con = request->getParam(0);
      AsyncWebParameter* gen = request->getParam(1);
      updateleds(con->name().toInt(), gen->name().toInt());
      request->send(200, "text/plain", "message received"); });
}

void setup()
{
  WiFi.begin(ssid, password);

  for (int i = 0; i < 20; i++)
  {
    con_led[i].set_debug_mode(true);
  }

  Serial.begin(9600);

  FastLED.addLeds<WS2812B, data_pin, RGB>(led_strip, num_leds);

  int i;
  while (WiFi.status() != WL_CONNECTED)
  {
    i++;
    led_strip[i] = con_led[i].get_color();
    FastLED.show();
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

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