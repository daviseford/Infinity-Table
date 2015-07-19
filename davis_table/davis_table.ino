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
  strip.setBrightness(55);  // Lower brightness and save eyeballs
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  connectingPixelsBlack(25);
  connectingPixels(20);
  davisRandomChaser(15);
  amandaColors(20);
  rainbowCycle(15);
  rainbowFull(15);
  rainbowDavis(15);
  colorWave(13);
  colorWipe(strip.Color(0, 0, 0), 100); // Black

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

int returnNumber(int number) {
  return number;
}


void connectingPixels( uint8_t wait) {
  int i, looper, tick, northEastCounter, southEastCounter, northWestCounter, southWestCounter, northPixel, southPixel, eastPixel, westPixel, remainder;
  int traceR, traceG, traceB, bgR, bgG, bgB, tracerLength;

  northPixel = 150; // pixel at the top of the table
  southPixel = 63;  //pixel at the bottom of the table
  eastPixel = 108;  // right side halfway point
  westPixel = 18;   // left side

  traceR = rand() % 255; // re-roll the random dice every time a loop is completed
  traceG = rand() % 255; // we need a value between 0 and 255 (to pass in as RGB values)
  traceB = rand() % 255;

  bgR = 0; //background colors
  bgG = 0; //initialize these values to whatever you want
  bgB = 0; //they are only used on the first lap. think of it as "booting up"

  //tracerLength = 43; //this will make the ends  meet every time
  tracerLength = rand() % 43; //leave this enabled for a more random tracer sequence. you can set a minimum by modifying this to read rand() % 43 + 10 (or whatever)

  /* this loop controls the number of times the full sequence will run.
   * a full sequence begins with two pixels enabled in the middle of the north and south ends of the table
   * tracers are then deployed towards east and west ends of the table.
   * a sequence ends when the tracers return to their starting position and a new RGB value is generated
   * set cycle to 50 to see this effect 50 times, for example
   */
  for (int cycle = 0; cycle < 30; cycle++) {
    for (tick = 0; tick < tracerLength; tick++) {                                           // overall loop

      remainder = (northPixel + northWestCounter) - strip.numPixels();

      /*If our remainder is positive, that means we've crossed over from LED 174 to LED 0.
      * So, we add our counter and starting position (northPixel), and subtract the number of LEDs.
      * The remainder is what needs to be added to 0 to keep the led update pushing from 0-18    *
       */

      for (i = 0; i < strip.numPixels(); i++) {                                   // led update loop
        if (i == southPixel || i == northPixel) {                                 // always leave these on, since they're our marker for north/south
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i <= northPixel + northWestCounter && i > northPixel ) {         // start sending a red wave out from the northPixel, +1 every tick
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (remainder >= 0 && i >= 0 && i <= remainder && i <= westPixel) {  // if the remainder is greater than 0 (i.e. we have overrun the number of LEDs in the strip)
          strip.setPixelColor(i, traceR, traceG, traceB);                         // fill up to the remainder (which will be between 0-18)
        }                                                                         // this is just to handle going from LED 174 -> 0 -> 1 -> etc

        else if (i >= northPixel + northEastCounter && i <= northPixel && i >= eastPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i >= southPixel + southWestCounter && i <= southPixel && i >= westPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i <= southPixel + southEastCounter && i >= southPixel && i <= eastPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
      }

      strip.show();
      delay(wait);

      northWestCounter++;
      northEastCounter--;
      southWestCounter--;
      southEastCounter++;
    }

    for (tick = 0; tick < tracerLength; tick++) {                                           // this loop reverses the tracer, filling the background color behind it

      remainder = (northPixel + northWestCounter) - strip.numPixels();

      /*If our remainder is positive, that means we've crossed over from LED 174 to LED 0.
      * So, we add our counter and starting position (northPixel), and subtract the number of LEDs.
      * The remainder is what needs to be added to 0 to keep the led update pushing from 0-18    *
       */

      for (i = 0; i < strip.numPixels(); i++) {                                   // led update loop
        if (i == southPixel || i == northPixel) { //always leave these on, since they're our marker for north/south
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i <= northPixel + northWestCounter && i > northPixel ) {         // start sending a red wave out from the northPixel, +1 every tick
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (remainder >= 0 && i >= 0 && i <= remainder && i <= westPixel) {  // if the remainder is greater than 0 (i.e. we have overrun the number of LEDs in the strip)
          strip.setPixelColor(i, traceR, traceG, traceB);                         // fill up to the remainder (which will be between 0-18)
        }                                                                         // this is just to handle going from LED 174 -> 0 -> 1 -> etc

        else if (i >= northPixel + northEastCounter && i <= northPixel && i >= eastPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i >= southPixel + southWestCounter && i <= southPixel && i >= westPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i <= southPixel + southEastCounter && i >= southPixel && i <= eastPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else {
          strip.setPixelColor(i, bgR, bgG, bgB);
        }
      }

      strip.show();
      delay(wait);

      northWestCounter--;
      northEastCounter++;
      southWestCounter++;
      southEastCounter--;
    }

    northEastCounter = 0;
    northWestCounter = 0;
    southEastCounter = 0;
    southWestCounter = 0;

    bgR = returnNumber(traceR);
    bgG = returnNumber(traceG);
    bgB = returnNumber(traceB);

    traceR = rand() % 255;                                                     // re-roll the random dice every time a loop is completed
    traceG = rand() % 255;
    traceB = rand() % 255;

    //tracerLength = 43; //this will make the ends  meet every time
    tracerLength = rand() % 43; //leave this enabled for a more random tracer sequence. you can set a minimum by modifying this to read rand() % 43 + 10 (or whatever)
  }
}


void connectingPixelsBlack( uint8_t wait) {
  int i, looper, tick, northEastCounter, southEastCounter, northWestCounter, southWestCounter, northPixel, southPixel, eastPixel, westPixel, remainder;
  int traceR, traceG, traceB, bgR, bgG, bgB;

  northPixel = 150;                                                               // pixel at the top of the table
  southPixel = 63;
  eastPixel = 108;                                                                // right side halfway point
  westPixel = 18;                                                                 // left side

  traceR = rand() % 255;                                                     // re-roll the random dice every time a loop is completed
  traceG = rand() % 255;
  traceB = rand() % 255;

  bgR = 0; //initialize these values to whatever you want
  bgG = 0;
  bgB = 0;

  /* this loop controls the number of times the full sequence will run.
   * a full sequence begins with two pixels enabled in the middle of the north and south ends of the table
   * tracers are then deployed towards east and west ends of the table.
   * a sequence ends when the tracers return to their starting position and a new RGB value is generated
   * set cycle to 50 to see this effect 50 times, for example
   */
  for (int cycle = 0; cycle < 30; cycle++) {
    for (tick = 0; tick < 43; tick++) {                                           // overall loop

      remainder = (northPixel + northWestCounter) - strip.numPixels();

      /*If our remainder is positive, that means we've crossed over from LED 174 to LED 0.
      * So, we add our counter and starting position (northPixel), and subtract the number of LEDs.
      * The remainder is what needs to be added to 0 to keep the led update pushing from 0-18    *
       */

      for (i = 0; i < strip.numPixels(); i++) {                                   // led update loop
        if (i == southPixel || i == northPixel) {                                 // always leave these on, since they're our marker for north/south
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i <= northPixel + northWestCounter && i > northPixel ) {         // start sending a red wave out from the northPixel, +1 every tick
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (remainder >= 0 && i >= 0 && i <= remainder && i <= westPixel) {  // if the remainder is greater than 0 (i.e. we have overrun the number of LEDs in the strip)
          strip.setPixelColor(i, traceR, traceG, traceB);                         // fill up to the remainder (which will be between 0-18)
        }                                                                         // this is just to handle going from LED 174 -> 0 -> 1 -> etc

        else if (i >= northPixel + northEastCounter && i <= northPixel && i >= eastPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i >= southPixel + southWestCounter && i <= southPixel && i >= westPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i <= southPixel + southEastCounter && i >= southPixel && i <= eastPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
      }

      strip.show();
      delay(wait);

      northWestCounter++;
      northEastCounter--;
      southWestCounter--;
      southEastCounter++;
    }

    for (tick = 0; tick < 43; tick++) {                                           // this loop reverses the tracer, filling the background color behind it

      remainder = (northPixel + northWestCounter) - strip.numPixels();

      /*If our remainder is positive, that means we've crossed over from LED 174 to LED 0.
      * So, we add our counter and starting position (northPixel), and subtract the number of LEDs.
      * The remainder is what needs to be added to 0 to keep the led update pushing from 0-18    *
       */

      for (i = 0; i < strip.numPixels(); i++) {                                   // led update loop
        if (i == southPixel || i == northPixel) { //always leave these on, since they're our marker for north/south
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i <= northPixel + northWestCounter && i > northPixel ) {         // start sending a red wave out from the northPixel, +1 every tick
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (remainder >= 0 && i >= 0 && i <= remainder && i <= westPixel) {  // if the remainder is greater than 0 (i.e. we have overrun the number of LEDs in the strip)
          strip.setPixelColor(i, traceR, traceG, traceB);                         // fill up to the remainder (which will be between 0-18)
        }                                                                         // this is just to handle going from LED 174 -> 0 -> 1 -> etc

        else if (i >= northPixel + northEastCounter && i <= northPixel && i >= eastPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i >= southPixel + southWestCounter && i <= southPixel && i >= westPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else if (i <= southPixel + southEastCounter && i >= southPixel && i <= eastPixel) {
          strip.setPixelColor(i, traceR, traceG, traceB);
        }
        else {
          strip.setPixelColor(i, 0, 0, 0);
        }
      }

      strip.show();
      delay(wait);

      northWestCounter--;
      northEastCounter++;
      southWestCounter++;
      southEastCounter--;
    }

    northEastCounter = 0;
    northWestCounter = 0;
    southEastCounter = 0;
    southWestCounter = 0;

    bgR = returnNumber(traceR);
    bgG = returnNumber(traceG);
    bgB = returnNumber(traceB);

    traceR = rand() % 255;                                                     // re-roll the random dice every time a loop is completed
    traceG = rand() % 255;
    traceB = rand() % 255;
  }
}

// Experimenting with a chaser that bounces back and forth.
// -Davis
void davisRandomChaser(uint8_t wait) {
  uint16_t i, j, tick, cycle;
  cycle = 15; //how many times we'll do a full loop (forward and back)
  for (tick = 0; tick < cycle; tick++) {

    int randomRed = rand() % 255; //re-roll the random dice every time a loop is completed
    int randomGreen = rand() % 255;
    int randomBlue = rand() % 255;

    for (j = strip.numPixels(); j > 0; j--) {

      for (i = 0; i < strip.numPixels(); i++) {
        if (j % strip.numPixels() == i) {
          strip.setPixelColor(i, randomRed, randomGreen, randomBlue);
          strip.setPixelColor(i - 1, randomRed, randomGreen, randomBlue);
          strip.setPixelColor(i - 2, randomRed, randomGreen, randomBlue);
          strip.setPixelColor(i - 3, randomRed, randomGreen, randomBlue);
        }
        else {
          strip.setPixelColor(i, 0, 0, 64); //blue
        }

      }

      strip.show();
      delay(wait);
    }

    for (j = 0; j < strip.numPixels(); j++) {

      for (i = 0; i < strip.numPixels(); i++) {
        if (j % strip.numPixels() == i) {
          strip.setPixelColor(i, randomRed, randomGreen, randomBlue);
          strip.setPixelColor(i - 1, randomRed, randomGreen, randomBlue);
          strip.setPixelColor(i - 2, randomRed, randomGreen, randomBlue);
          strip.setPixelColor(i - 3, randomRed, randomGreen, randomBlue);
        }
        else {
          strip.setPixelColor(i, 0, 0, 64); //blue
        }

      }

      strip.show();
      delay(wait);
    }
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
  cycle = stripsize * 7; // times around the circle...

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


int* amandaColorHolder(int selection) {

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

/*  Amanda's Custom Color Sequence, with automatic RGB value blending!
 *
 *  The following is a cheap way of incrementing/decrementing RGB values
 *  in order to produce a blending effect. We set the target RGB to pEndcolor,
 *  which is an array with 3 values [R, G, B]. The program will step through
 *  our r,g, and b variables and check them against the target. If the target value
 *  is greater than the current value, we increment the current value and check it again on the next loop.
 *
 *  When r,g, and b are equal to pEndColor[R,G,B]
 *  we increment the caseNum variable (passed to amandaColorHolder), which gives us our next target.
 *
 *  Notes: This isn't a mathematically perfect way of fading between colors. ¯\_(ツ)_/¯
 *
 *  Example of limitation:
 *
 *  Going from (255, 20, 20) to (255, 0, 0) will take twenty iterations.
 *  Going from (255, 255, 255) to (255, 0, 0) will take two hundred fifty five iterations.
 *  This means there is a time variance (colors appear for different lengths of time,
 *  depending on their RGB distance from the next value)
 *
 *  This can lead to flickering sequences with color values that are too close together.
 *
 *  -Davis Ford, 7/6/2015
 */

void amandaColors(uint8_t wait) {
  uint16_t i, j, caseNum;
  int * pStartColor, * pEndColor; //credit to Matthew Ibarra (pengii23) for figuring out my pointers
  pStartColor = amandaColorHolder(0); //initializes with case 0 (red)
  pEndColor = amandaColorHolder(1); //sets up the target values
  int r = pStartColor[0]; //since our first case is red, r = 255
  int b = pStartColor[1]; //0
  int g = pStartColor[2]; //0


  for (j = 0; j < 256 * 10; j++) {

    if (caseNum > 51) { //52 cases above in amandaColorHolder
      caseNum = 0;
    }

    if (r < pEndColor[0]) {
      r++;
    }
    else if (r > pEndColor[0]) {
      r--;
    }


    if (g < pEndColor[1]) {
      g++;
    }
    else if (g > pEndColor[1]) {
      g--;
    }

    if (b < pEndColor[2]) {
      b++;
    }
    else if (b > pEndColor[2]) {
      b--;
    }

    /*
    * Set all pixels on the strip to the current r,g,b values
    */
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, r, g, b);
    }

    strip.show();
    delay(wait);

    /*  Check to see if r,g,b are equal to our target values.
     *  If they are, increment caseNum (gives us a new target value)
     *  and assign the new [R,G,B] values to pEndColor.
     */
    if (r == pEndColor[0] && g == pEndColor[1] && b == pEndColor[2]) {
      caseNum++;
      pEndColor = amandaColorHolder(caseNum);
    }

  }
}
