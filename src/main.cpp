#include "Arduino.h"
#include <FastLED.h>
#define NUM_LEDS 16 
#define LED_PIN 16
CRGB leds[NUM_LEDS];
uint8_t hue = 0;


uint8_t palIdx = 0;


void setup()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(180);
    //FastLED.setBrightness(80);
    FastLED.setCorrection(UncorrectedColor);

    FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);
}

CRGBPalette16 nor = CRGBPalette16 (
    CRGB(186, 12, 47), CRGB(186, 12, 47), CRGB(186, 12, 47), CRGB(186, 12, 47), 
    
    CRGB(0, 32, 91), CRGB(0, 32, 91), CRGB(0, 32, 91),
    CRGB(255, 255, 255), CRGB(255, 255, 255), 
    CRGB(0, 32, 91),CRGB(0, 32, 91), CRGB(0, 32, 91),
    CRGB(186, 12, 47), CRGB(186, 12, 47), CRGB(186, 12, 47), CRGB(186, 12, 47)

);

void loop()
{

    // for (int i = 0; i < NUM_LEDS; i++) {
    //     leds[i] = CRGB::Green; //CHSV(hue, 255, 255);
    // }
    // EVERY_N_MILLIS(35){
    //     hue++;
    // }


    //FastLED.setCorrection(TypicalLEDStrip);
    //FastLED.setCorrection(UncorrectedColor);
    EVERY_N_SECONDS(1) {
        fill_palette(leds, NUM_LEDS, palIdx, 255/NUM_LEDS, nor, 255, NOBLEND); //LINEARBLEND, NOBLEND

    }


    
    FastLED.show();




	// leds[0] = CRGB::White; FastLED.show(); delay(300);
	// leds[0] = CRGB::Black; FastLED.show(); delay(300);
}