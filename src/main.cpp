#include "Arduino.h"
#include "easing.h"
#include <FastLED.h>
#include <sstream>
#include "ota.h"

#define NUM_LEDS 88 
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

CRGBPalette16 nor = CRGBPalette16 (
    CRGB(186, 12, 47), CRGB(186, 12, 47), CRGB(186, 12, 47), CRGB(186, 12, 47), 
    
    CRGB(0, 32, 91), CRGB(0, 32, 91), CRGB(0, 32, 91),
    CRGB(255, 255, 255), CRGB(255, 255, 255), 
    CRGB(0, 32, 91),CRGB(0, 32, 91), CRGB(0, 32, 91),
    CRGB(186, 12, 47), CRGB(186, 12, 47), CRGB(186, 12, 47), CRGB(186, 12, 47)
);

 CHSVPalette16 nor2 = CHSVPalette16(
    CHSV(350, 85, 42), CHSV(350, 85, 42), CHSV(350, 85, 42), CHSV(350, 85, 42), 
    CHSV(350, 85, 42), CHSV(350, 85, 42), CHSV(350, 85, 42), 
    CHSV(350, 85, 42), CHSV(350, 85, 42), 
    CHSV(350, 85, 42), CHSV(350, 85, 42), CHSV(350, 85, 42), 
    CHSV(0, 100, 100), CHSV(0, 100, 100), CHSV(0, 100, 100), CHSV(0, 100, 100)
 );


double deg = 0.0;
bool forward = true;

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

    // EVERY_N_SECONDS(1) {
    //     fill_palette(leds, NUM_LEDS, palIdx, 255/NUM_LEDS, nor, 255, NOBLEND); //LINEARBLEND, NOBLEND
    // }

    EVERY_N_MILLISECONDS(25) {
        auto easingFunction = getEasingFunction(EaseInOutCirc);


        if (deg >= 1) { forward = false; }
        else if (deg <= 0) { forward = true; };
        
        if (forward) { deg += 0.005; } else { deg -= 0.005; }

        if (deg <= 0) {deg = 0.0;}
        if (deg >= 1) { deg = 1.0; }

        std::stringstream ss;
        ss << deg << " deg";
        // Serial.print("Deg ");
        // Serial.print(deg);
        // Serial.print(", pos ");
        // Serial.println(easingFunction(deg) * NUM_LEDS);
        pos = easingFunction(deg) * (NUM_LEDS / 2);

    }

    // EVERY_N_MILLISECONDS(40) {
    //     pos++;
    //     if (pos >= NUM_LEDS) pos = 0;
    // }

    EVERY_N_MILLISECONDS(20) {
        

        for (int i = 0; i < NUM_LEDS; i++) {
            if (ledHSV[i].val > 5) ledHSV[i].val -= 5;
            if (ledHSV[i].val > 0 && ledHSV[i].val <= 10) ledHSV[i].val = 0;
            //leds[i] = CRGB::Green; //CHSV(hue, 255, 255);
        }

    }

    EVERY_N_MILLISECONDS(15) {
        CHSV color = ColorFromPalette(nor2, 9, 255, LINEARBLEND);
        ledHSV[pos] = color;
    }

    EVERY_N_MILLIS(200) {
        //fadeUsingColor(leds, NUM_LEDS, ColorFromPalette(nor, 9, 190, NOBLEND));
        //fadeLightBy(leds, NUM_LEDS, 90);
        fadeToBlackBy(leds, NUM_LEDS, 1);
    }
    
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ledHSV[i];
    }


    FastLED.show();


    EVERY_N_MILLIS(100) {
        OTA::handle();
    }


	// leds[0] = CRGB::White; FastLED.show(); delay(300);
	// leds[0] = CRGB::Black; FastLED.show(); delay(300);
}