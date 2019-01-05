#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    131
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

SoftwareSerial mySoftwareSerial(2,3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup()
{
  pinMode(4,INPUT_PULLUP);
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  myDFPlayer.begin(mySoftwareSerial);
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(16); 
  myDFPlayer.randomAll();  
  myDFPlayer.enableLoopAll();

  delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
}

void loop()
{
  if(!digitalRead(4)){
    myDFPlayer.next();
    delay(50);
  }
  currentPalette = RainbowColors_p;  
  currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
    
  FillLEDsFromPaletteColors( startIndex);
    
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
