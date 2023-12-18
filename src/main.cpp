#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 4
#define DATA_PIN 1
#define COLOR_ORDER GRB

// leds array
CRGB leds[NUM_LEDS];

// put function declarations here:
// int myFunction(int, int);

void setup()
{
  // pinMode(LED_BUILTIN, OUTPUT);
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);

  // int result = myFunction(2, 3);
}

void loop()
{
  // put your main code here, to run repeatedly:
  // digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  // delay(1000);                     // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  // delay(1000);

  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(500);

  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}

// put function definitions here:
// int myFunction(int x, int y)
// {
//   return x + y;
// }