#include "FastLED.h"

// MODIFIED FastLED "just-100-lines-of-code" demo reel
//
// This example also shows one easy way to define multiple 
// TWO-ARGUMENT animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, January 2015

#if FASTLED_VERSION < 3001000
#error "Requires newer version of FastLED; check github for latest code."
#endif

#define DATA_PIN    1
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    174
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          64

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

// List of patterns to cycle through.  Each is defined as a separate function below.
// Each pattern is defined as a function that takes two uint8_t's; all of the pattern functions
// have to have the same signature in this setup, and two (hardcoded!) parameters can be 
// passed to each one:

typedef void (*TwoArgumentPattern)(uint8_t arg1, uint8_t arg2);
typedef struct { 
  TwoArgumentPattern mPattern;
  uint8_t mArg1;
  uint8_t mArg2;
} TwoArgumentPatterWithArgumentValues;

TwoArgumentPatterWithArgumentValues gPatternsAndArguments[] = {

  //{applause},
  {pride2015},
  
  {rainbowWithGlitter_2,  5 /*stripeDensity*/,  0 /*chanceOfGlitter*/},
  {rainbowWithGlitter_2, 10 /*stripeDensity*/, 20 /*chanceOfGlitter*/},

  {sinelon_2, 13 /*BPM*/, 10 /*fadeAmount*/ },
  {sinelon_2,  7 /*BPM*/, 1 /*fadeAmount*/ },
  
  {bpm_2,     62 /*BPM*/, 3 /*stripeWidth*/},
  {bpm_2,    125 /*BPM*/, 7 /*stripeWidth*/},
  {bpm_2,     15 /*BPM*/, 1 /*stripeWidth*/},
  
  //{confetti_2, 96 /*colorVariation*/, 30/*fadeAmount*/},
  //{confetti_2, 16 /*colorVariation*/,  3/*fadeAmount*/},
  
  {juggle_2,  3 /*numDots*/,  7 /*baseBpmSpeed*/},
  {juggle_2,  22 /*numDots*/, 13 /*baseBpmSpeed*/},

  

  
};


uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  gHue++; // slowly cycle the "base color" through the rainbow

  // Call the current pattern function once, updating the 'leds' array
  uint8_t arg1 = gPatternsAndArguments[ gCurrentPatternNumber ].mArg1;
  uint8_t arg2 = gPatternsAndArguments[ gCurrentPatternNumber ].mArg2;
  TwoArgumentPattern pat = gPatternsAndArguments[ gCurrentPatternNumber ].mPattern;
  
  pat(arg1, arg2);
  
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/120); // about sixty FPS

  EVERY_N_SECONDS(15) { nextPattern(); } // change patterns periodically
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  const int numberOfPatterns = sizeof(gPatternsAndArguments) / sizeof( gPatternsAndArguments[0]);  
  gCurrentPatternNumber = (gCurrentPatternNumber+1) % numberOfPatterns;
}


void rainbowWithGlitter_2( uint8_t stripeDensity, uint8_t chanceOfGlitter) 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  fill_rainbow( leds, NUM_LEDS, gHue, stripeDensity);
  addGlitter(chanceOfGlitter);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti_2( uint8_t colorVariation, uint8_t fadeAmount)
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, fadeAmount);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(colorVariation), 200, 255);
}

void sinelon_2( uint8_t bpmSpeed, uint8_t fadeAmount)
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, fadeAmount);
  int pos = beatsin16(bpmSpeed, 0, NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm_2( uint8_t bpmSpeed, uint8_t stripeWidth)
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = bpmSpeed;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(palette, gHue+(i*stripeWidth), beat);
  }
}

void juggle_2( uint8_t numDots, uint8_t baseBpmSpeed) {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 100);
  byte dothue = 0;
  for( int i = 0; i < numDots; i++) {
    leds[beatsin16(i+baseBpmSpeed,0,NUM_LEDS)] |= CHSV(dothue, 255, 224);
    dothue += (256 / numDots);
  }
}

void applause(uint8_t numDots, uint8_t baseBpmSpeed)
{
  static uint16_t lastPixel = 0;
  fadeToBlackBy( leds, NUM_LEDS, 32);
  leds[lastPixel] = CHSV(random8(HUE_BLUE,HUE_PURPLE),255,255);
  lastPixel = random16(NUM_LEDS);
  leds[lastPixel] = CRGB::White;
}

void pride2015(uint8_t numDots, uint8_t baseBpmSpeed) 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;
    
    nblend( leds[pixelnumber], newcolor, 64);
  }
}
