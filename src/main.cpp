#include "Arduino.h"
#include "easing.h"
#include <FastLED.h>
#include <sstream>
#include <random>
#include "ota.h"

#define NUM_LEDS 71 
#define LED_STRIP1_PIN GPIO_NUM_16
#define LED_STRIP2_PIN GPIO_NUM_17

CRGB strip_1[NUM_LEDS];
CRGB strip_2[NUM_LEDS];

void setup()
{
    Serial.begin(9600);
    Serial.println("Starter");
    FastLED.addLeds<WS2812B, LED_STRIP1_PIN, GRB>(strip_1, NUM_LEDS);
    FastLED.addLeds<WS2812B, LED_STRIP2_PIN, GRB>(strip_2, NUM_LEDS);

    //FastLED.setBrightness(80);
    FastLED.setCorrection(UncorrectedColor);
    FastLED.setBrightness(20);

    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
    OTA::setup();
    
}

CRGB colors[] = {
    CRGB::PaleTurquoise,
    CRGB::Pink,
    CRGB::MidnightBlue,
    CRGB::Chocolate,
    CRGB::SpringGreen,
};

CRGB randomColor() {
    int size = sizeof(colors) / sizeof(colors[0]);
    auto randomIndex = rand() % size;
    return colors[randomIndex];
}

bool firstRun = true;


void loop()
{

    EVERY_N_MILLIS(50) {
        //fadeUsingColor(leds, NUM_LEDS, ColorFromPalette(nor, 9, 190, NOBLEND));
        //fadeLightBy(leds, NUM_LEDS, 90);
        fadeToBlackBy(strip_1, NUM_LEDS, 3);
        fadeToBlackBy(strip_2, NUM_LEDS, 3);

    }
    
    if (firstRun) {
        firstRun = false;
        int randInterval = 6+ (rand() % 10);

        for (int i = 0; i < NUM_LEDS; i++) {
            if (i%randInterval == 0) {
                strip_1[i] = randomColor();
                strip_2[i] = randomColor();
            }
        //leds[i] = ledHSV[i];
        }
    }

    EVERY_N_MILLIS(5000) {
        int randInterval = 6+ (rand() % 10);
        int randInterval2 = 6+ (rand() % 10);

        for (int i = 0; i < NUM_LEDS; i++) {
            if (i%randInterval == 0) {
                strip_1[i] = randomColor();
            }
             if (i%randInterval2 == 0) {
                strip_2[i] = randomColor();
            }
        //leds[i] = ledHSV[i];
        }
    }
    
    FastLED.setBrightness(20);
    FastLED.show();

    EVERY_N_MILLIS(300) {
        OTA::handle();
    }


	// leds[0] = CRGB::White; FastLED.show(); delay(300);
	// leds[0] = CRGB::Black; FastLED.show(); delay(300);
}