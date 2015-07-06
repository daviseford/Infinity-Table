#include <Adafruit_NeoPixel.h>

#define PINdroite 1
#define STRIPSIZE 174

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, PINdroite, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(60);  // Lower brightness and save eyeballs OR NOT
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  testColors(20);
  //  amandaColors(20);
  //  solidColors(15);
  //  rainbowCycle(15);
  //  northSouthChaseFull(15);
  //  rainbowFull(15);
  //  rainbowDavis(15);
  //  colorWave(8);
  //  rainbowCycleNorthSouth(15);
  //  colorWipe(strip.Color(0,0,0), 100); // Black

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/**
 *      ^   ^   ^
 * ~~~~~ ColorWave ~~~~~
 *        V   V   V
 */
void colorWave(uint8_t wait) {
  int i, j, stripsize, cycle;
  float ang, rsin, gsin, bsin, offset;

  static int tick = 0;

  stripsize = strip.numPixels();
  cycle = stripsize * 5; // times around the circle...

  while (++tick % cycle) {
    offset = map2PI(tick);

    for (i = 0; i < stripsize; i++) {
      ang = map2PI(i) - offset;
      rsin = sin(ang);
      gsin = sin(2.0 * ang / 3.0 + map2PI(int(stripsize / 6)));
      bsin = sin(4.0 * ang / 5.0 + map2PI(int(stripsize / 3)));
      strip.setPixelColor(i, strip.Color(trigScale(rsin), trigScale(gsin), trigScale(bsin)));
    }

    strip.show();
    delay(wait);
  }

}

/**
 * Scale a value returned from a trig function to a byte value.
 * [-1, +1] -> [0, 254]
 * Note that we ignore the possible value of 255, for efficiency,
 * and because nobody will be able to differentiate between the
 * brightness levels of 254 and 255.
 */
byte trigScale(float val) {
  val += 1.0; // move range to [0.0, 2.0]
  val *= 127.0; // move range to [0.0, 254.0]

  return int(val) & 255;
}

/**
 * Map an integer so that [0, striplength] -> [0, 2PI]
 */
float map2PI(int i) {
  return PI * 2.0 * float(i) / float(strip.numPixels());
}

void offsetChaser(uint16_t i, uint16_t j, uint16_t offset) {
  uint16_t baseNum = i - offset;
  strip.setPixelColor(baseNum, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
  strip.setPixelColor(baseNum - 1, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
  strip.setPixelColor(baseNum - 2, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
  strip.setPixelColor(baseNum - 3, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
}

//I DONT KNOW WHAT IM DOING EXACTLY
void davisChaser(uint8_t wait) {
  uint16_t i, j, c, tickSpeed;
  tickSpeed = 2;
  c = strip.numPixels();

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel

    for (i = 0; i < strip.numPixels(); i++) {

      if ((j * tickSpeed) % strip.numPixels() == i) {



        offsetChaser(i, j, 0);
        offsetChaser(i, j, 36);
        offsetChaser(i, j, 72);
        offsetChaser(i, j, 108);
        offsetChaser(i, j, 144);
        offsetChaser(i, j, 180);
        offsetChaser(i, j, 216);

      }
      else {
        strip.setPixelColor(i, 0, 0, 0); //black
      }
    }
    strip.show();
    delay(wait);
  }
}


//I DONT KNOW WHAT IM DOING EXACTLY
void rainbowDavis(uint8_t wait) {
  uint16_t i, j, c, tickSpeed;
  tickSpeed = 2;
  c = strip.numPixels();

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel

    for (i = 0; i < strip.numPixels(); i++) {

      if ((j * tickSpeed) % strip.numPixels() == i) {
        offsetChaser(i, j, 0);
        offsetChaser(i, j, 36);
        offsetChaser(i, j, 72);
        offsetChaser(i, j, 108);
        offsetChaser(i, j, 144);
        offsetChaser(i, j, 180);
        offsetChaser(i, j, 216);

      }
      else {
        strip.setPixelColor(i, 0, 0, 0); //black
      }
    }
    strip.show();
    delay(wait);
  }
}

void rainbowFull(uint8_t wait) {
  uint16_t i, j, c, tickSpeed;
  tickSpeed = 1;
  c = strip.numPixels();

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel

    for (i = 0; i < strip.numPixels() * 2; i++) {

      if ((j * tickSpeed) % strip.numPixels() == i) {
        offsetChaser(i, j, 0);
        offsetChaser(i, j, 36);
        offsetChaser(i, j, 72);
        offsetChaser(i, j, 108);
        offsetChaser(i, j, 144);
        offsetChaser(i, j, 180);
        offsetChaser(i, j, 216);

      }
      else {
        //strip.setPixelColor(i, 0, 0, 0); //black
      }
    }
    strip.show();
    delay(wait);
  }
}


//DAVIS
void offsetChaserNorthSouth(uint16_t i, uint16_t j, uint16_t offset) {
  uint16_t baseNum = i - offset;
  if ((baseNum - 3) > 36 && baseNum < 90) { //36-90 seems to account for the South Array
    strip.setPixelColor(baseNum, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
    strip.setPixelColor(baseNum - 1, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
    strip.setPixelColor(baseNum - 2, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
    strip.setPixelColor(baseNum - 3, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
  }
  else if ((baseNum - 3) > 122) { //122 and up go to the end
    strip.setPixelColor(baseNum, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
    strip.setPixelColor(baseNum - 1, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
    strip.setPixelColor(baseNum - 2, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
    strip.setPixelColor(baseNum - 3, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //fuckin' rainbows
  }
  else {
    strip.setPixelColor(i, 0, 0, 0); //black
  }
}

//attempting to selectively light two tables sides, north and south
void northSouthChaseFull(uint8_t wait) {
  uint16_t i, j, c, tickSpeed;
  tickSpeed = 2;
  c = strip.numPixels();

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel

    for (i = 0; i < strip.numPixels(); i++) {

      if ((j * tickSpeed) % strip.numPixels() == i) {
        offsetChaserNorthSouth(i, j, 0);
        offsetChaserNorthSouth(i, j, 36);
        offsetChaserNorthSouth(i, j, 72);

      }
      else {
        //strip.setPixelColor(i, 0, 0, 0); //black
      }
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycleNorthSouth(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      if (i > 35 && i < 90) {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      }
      else if (i > 122) {
        strip.setPixelColor(0, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //a little hacky, but 122+, and 0-1, are necessary for North Side
        strip.setPixelColor(1, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      }
      else {
        strip.setPixelColor(i, 0, 0, 0); //black
      }
    }
    strip.show();
    delay(wait);
  }
}

uint32_t amandaColorHolder(int selection) {


  switch (selection) {
    case 0:
      return strip.Color(255, 0, 0); //red
      break;

    case 1:
      return strip.Color(255, 25, 25);
      break;

    case 2:
      return strip.Color(255, 48, 48);
      break;

    case 3:
      return strip.Color(255, 89, 89);
      break;

    case 4:
      return strip.Color(255, 122, 122);
      break;

    case 5:
      return strip.Color(255, 162, 162);
      break;

    case 6:
      return strip.Color(255, 162, 162);
      break;

    case 7:
      return strip.Color(255, 204, 204); //pink
      break;

    case 8:
      return strip.Color(255, 204, 255);
      break;

    case 9:
      return strip.Color(255, 153, 255); //periwinkle pink
      break;

    case 10:
      return strip.Color(255, 102, 255); //
      break;

    case 11:
      return strip.Color(255, 0, 255); //
      break;

    case 12:
      return strip.Color(255, 51, 204); //
      break;

    case 13:
      return strip.Color(255, 51, 153); //
      break;

    case 14:
      return strip.Color(255, 0, 102); // tangerine
      break;

    case 15:
      return strip.Color(255, 80, 80); // orange
      break;

    case 16:
      return strip.Color(255, 102, 0); // orange
      break;

    case 17:
      return strip.Color(255, 153, 51); //
      break;

    case 18:
      return strip.Color(255, 204, 0); //golden
      break;

    case 19:
      return strip.Color(255, 255, 0); //yellow
      break;

    case 20:
      return strip.Color(255, 255, 102); //
      break;

    case 21:
      return strip.Color(255, 255, 153); //
      break;

    case 22:
      return strip.Color(255, 255, 204); //
      break;

    case 23:
      return strip.Color(204, 255, 153); //
      break;

    case 24:
      return strip.Color(153, 255, 102); // light green
      break;

    case 25:
      return strip.Color(102, 255, 102); //
      break;

    case 26:
      return strip.Color(0, 255, 0); //lime green
      break;

    case 27:
      return strip.Color(0, 204, 0); //
      break;

    case 28:
      return strip.Color(0, 204, 102); //
      break;

    case 29:
      return strip.Color(0, 204, 153); //
      break;

    case 30:
      return strip.Color(77, 219, 184); //
      break;

    case 31:
      return strip.Color(0, 153, 153); //
      break;

    case 32:
      return strip.Color(0, 102, 153); //
      break;

    case 33:
      return strip.Color(0, 153, 204); //
      break;

    case 34:
      return strip.Color(0, 102, 204); //
      break;

    case 35:
      return strip.Color(0, 51, 204); //
      break;

    case 36:
      return strip.Color(0, 0, 255); // blue
      break;

    case 37:
      return strip.Color(51, 51, 255); //
      break;

    case 38:
      return strip.Color(51, 102, 255); //
      break;

    case 39:
      return strip.Color(102, 153, 255); //
      break;

    case 40:
      return strip.Color(153, 204, 255); //
      break;

    case 41:
      return strip.Color(204, 204, 255); //
      break;

    case 42:
      return strip.Color(204, 153, 255); //
      break;

    case 43:
      return strip.Color(204, 102, 255); //
      break;

    case 44:
      return strip.Color(204, 51, 255); //
      break;

    case 45:
      return strip.Color(204, 0, 255); //
      break;

    case 46:
      return strip.Color(153, 0, 204); //
      break;

    case 47:
      return strip.Color(102, 0, 102); //
      break;

    case 48:
      return strip.Color(92, 0, 92); //
      break;

    case 49:
      return strip.Color(74, 0, 74); //
      break;

    case 50:
      return strip.Color(44, 0, 44); //
      break;

    case 51:
      return strip.Color(22, 0, 22); //
      break;

    case 52:
      return strip.Color(0, 0, 0); //black
      break;

    default:
      return strip.Color(0, 0, 0); //black
  }
}

//custom
void amandaColors(uint8_t wait) {
  uint16_t i, j, caseNum;

  for (j = 0; j < 100; j++) {
    if (caseNum > 52) { //52 cases above in amandaColorHolder
      caseNum = 0;
    }
    else {
      caseNum++;
    }
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, (amandaColorHolder(caseNum)));
      //check the case ahead and interpolate the moves
      //return to caseNum after interpolation
      //so caseNum RG(B) is (200) and caseNum+1 RG(B) is (222)
      //run until that interpolation finishes
    }
    strip.show();
    delay(wait * 30);
  }
}


int* testColorHolder(int selection) {

  int* pRgb;

  switch (selection) {
    case 0:
    {
      int rgb[3] = {255, 0, 0}; //red
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 1:
    {
      int rgb[3] = {255, 25, 25};
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 2:
    {
      int rgb[3] = {255, 48, 48};
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 3:
    {
      int rgb[3] = {255, 89, 89};
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 4:
    {
      int rgb[3] = {255, 122, 122};
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 5:
    {
      int rgb[3] = {255, 162, 162};
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 6:
    {
      int rgb[3] = {255, 162, 162};
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 7:
    {
      int rgb[3] = {255, 204, 204}; //pink
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 8:
    {
      int rgb[3] = {255, 204, 255};
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 9:
    {
      int rgb[3] = {255, 153, 255}; //periwinkle pink
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 10:
    {
      int rgb[3] = {255, 102, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 11:
    {
      int rgb[3] = {255, 0, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 12:
    {
      int rgb[3] = {255, 51, 204}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 13:
    {
      int rgb[3] = {255, 51, 153}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 14:
    {
      int rgb[3] = {255, 0, 102}; // tangerine
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 15:
    {
      int rgb[3] = {255, 80, 80}; // orange
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 16:
    {
      int rgb[3] = {255, 102, 0}; // orange
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 17:
    {
      int rgb[3] = {255, 153, 51}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 18:
    {
      int rgb[3] = {255, 204, 0}; //golden
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 19:
    {
      int rgb[3] = {255, 255, 0}; //yellow
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 20:
    {
      int rgb[3] = {255, 255, 102}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 21:
    {
      int rgb[3] = {255, 255, 153}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 22:
    {
      int rgb[3] = {255, 255, 204}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 23:
    {
      int rgb[3] = {204, 255, 153}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 24:
    {
      int rgb[3] = {153, 255, 102}; // light green
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 25:
    {
      int rgb[3] = {102, 255, 102}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 26:
    {
      int rgb[3] = {0, 255, 0}; //lime green
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 27:
    {
      int rgb[3] = {0, 204, 0}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 28:
    {
      int rgb[3] = {0, 204, 102}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 29:
    {
      int rgb[3] = {0, 204, 153}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 30:
    {
      int rgb[3] = {77, 219, 184}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 31:
    {
      int rgb[3] = {0, 153, 153}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 32:
    {
      int rgb[3] = {0, 102, 153}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 33:
    {
      int rgb[3] = {0, 153, 204}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 34:
    {
      int rgb[3] = {0, 102, 204}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 35:
    {
      int rgb[3] = {0, 51, 204}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 36:
    {
      int rgb[3] = {0, 0, 255}; // blue
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 37:
    {
      int rgb[3] = {51, 51, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 38:
    {
      int rgb[3] = {51, 102, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 39:
    {
      int rgb[3] = {102, 153, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 40:
    {
      int rgb[3] = {153, 204, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 41:
    {
      int rgb[3] = {204, 204, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 42:
    {
      int rgb[3] = {204, 153, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 43:
    {
      int rgb[3] = {204, 102, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 44:
    {
      int rgb[3] = {204, 51, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 45:
    {
      int rgb[3] = {204, 0, 255}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 46:
    {
      int rgb[3] = {153, 0, 204}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 47:
    {
      int rgb[3] = {102, 0, 102}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 48:
    {
      int rgb[3] = {92, 0, 92}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 49:
    {
      int rgb[3] = {74, 0, 74}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 50:
    {
      int rgb[3] = {44, 0, 44}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 51:
    {
      int rgb[3] = {22, 0, 22}; //
      pRgb = rgb;
      return pRgb;
      break;
    }
    case 52:
    {
      int rgb[3] = {0, 0, 0}; //black
      pRgb = rgb;
      return pRgb;
      break;
    }
    default:
    {
      int rgb[3] = {0, 0, 0}; //black
      pRgb = rgb;
      return pRgb;
    }
  }
}

//custom
void testColors(uint8_t wait) {
  uint16_t i, j, caseNum;
  int r, g, b;


  for (j = 0; j < 174 * 5; j++) {

  if (caseNum > 51) { //52 cases above in testColorHolder
      caseNum = 0;
    }

    // int currentCase = testColorHolder(caseNum);
    // int nextCase = testColorHolder(caseNum + 1);

    // int startColor[3] = { 0 };
    // int endColor[3] = { 0 };

    int * pStartColor, * pEndColor;
    pStartColor = testColorHolder(caseNum);
    pEndColor = testColorHolder(caseNum + 1);
    // int startColor [3] = {currentCase[0], currentCase[1], currentCase[2]};
    // int endColor [3] = {nextCase[0], nextCase[1], nextCase[2]};


    if (pStartColor[0] == pEndColor[0]) {
      r = pEndColor[0];
    }
    else if (pStartColor[0] < pEndColor[0]) {
      r = pStartColor[0];
      pStartColor[0]++;
    }
    else if (pStartColor[0] > pEndColor[0]) {
      r = pStartColor[0];
      pStartColor[0]--;
    }

    if (pStartColor[1] == pEndColor[1]) {
      g = pEndColor[1];
    }
    else if (pStartColor[1] < pEndColor[1]) {
      g = pStartColor[1];
      pStartColor[1]++;
    }
    else if (pStartColor[1] > pEndColor[1]) {
      g = pStartColor[1];
      pStartColor[1]--;
    }

    if (pStartColor[2] == pEndColor[2]) {
      b = pEndColor[2];
    }
    else if (pStartColor[2] < pEndColor[2]) {
      b = pStartColor[2];
      pStartColor[2]++;
    }
    else if (pStartColor[2] > pEndColor[2]) {
      b = pStartColor[2];
      pStartColor[2]--;
    }

    if (r == pEndColor[0] && g == pEndColor[1] && b == pEndColor[2]) {
      caseNum++;
    }



    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, r, g, b); //if value comparison doesn't work, turn red

    }
    strip.show();
    delay(wait / 3);
  }
}


// Slightly different, this makes the rainbow equally distributed throughout
void solidColors(uint8_t wait) {
  uint16_t i, j, c;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    c++;
    for (i = 0; i < strip.numPixels(); i++) {
      if (j % 58) {
        strip.setPixelColor(i, 116, 24, (0 + c));
      }
      else {
        //strip.setPixelColor(i, 201, 155, 75);
        //strip.setPixelColor(1, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        strip.setPixelColor(i, 116, 24, (0 + c));
      }
    }
    strip.show();
    delay(wait);
  }
}
