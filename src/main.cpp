#include "Arduino.h"
#include "easing.h"
#include <FastLED.h>
#include <sstream>
#include "ota.h"

#define NUM_LEDS 71 
#define LED_STRIP1_PIN GPIO_NUM_16
#define LED_STRIP2_PIN GPIO_NUM_17

CHSV ledHSV[NUM_LEDS];
CRGB leds[NUM_LEDS];
uint8_t hue = 0;


uint8_t palIdx = 0;


uint8_t pos = 0;


void setup()
{
    Serial.begin(9600);
    Serial.println("Starter");
    FastLED.addLeds<WS2812B, LED_STRIP1_PIN, GRB>(leds, NUM_LEDS);
    FastLED.addLeds<WS2812B, LED_STRIP2_PIN, GRB>(leds, NUM_LEDS);

    FastLED.setBrightness(255);
    //FastLED.setBrightness(80);
    FastLED.setCorrection(UncorrectedColor);

    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
    OTA::setup();
    
}

void loop()
{

    EVERY_N_MILLIS(30) {
        //fadeUsingColor(leds, NUM_LEDS, ColorFromPalette(nor, 9, 190, NOBLEND));
        //fadeLightBy(leds, NUM_LEDS, 90);
        fadeToBlackBy(leds, NUM_LEDS, 10);
    }
    
    EVERY_N_MILLIS(3000) {
        for (int i = 0; i < NUM_LEDS; i++) {
        if (i%10 == 0) {
            leds[i] = CRGB::Red;

        }
        //leds[i] = ledHSV[i];
    }
    }



    FastLED.show();


    EVERY_N_MILLIS(100) {
        OTA::handle();
    }


	// leds[0] = CRGB::White; FastLED.show(); delay(300);
	// leds[0] = CRGB::Black; FastLED.show(); delay(300);
}