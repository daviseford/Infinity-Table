#include <Adafruit_NeoPixel.h>

#define PINdroite 1
#define STRIPSIZE 60 * 4

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
  strip.setBrightness(75);  // Lower brightness and save eyeballs OR NOT
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  rainbowChaser(15);
  colorWipe(strip.Color(0,0,0), 100); // Black

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/**
  * Chaser
  */
void rainbowChaser () {
  uint32_t c, d, chaser;
uint16_t i, j, x, y;
    
    chaser = 3;
    x = tick % 384;
        c = GetColor(color % MAX_COLORS);       //color
        j = tick % (strip.numPixels()/chaser);
        for(i=0; i < strip.numPixels(); i++) {
            if(i % (strip.numPixels()/chaser) == j) {
                strip.setPixelColor(i, Wheel(((i * 384 / strip.numPixels() * (color%MAX_COLORS)) + x) % 384));        //first pixel
                strip.setPixelColor(i + 1, Wheel(((i * 384 / strip.numPixels() * (color%MAX_COLORS)) + x) % 384));    //second pixel
                strip.setPixelColor(i + 2, Wheel(((i * 384 / strip.numPixels() * (color%MAX_COLORS)) + x) % 384));
            }
            else {
                strip.setPixelColor(i, strip.Color(0,0,0));
            }
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
  cycle = stripsize * 25; // times around the circle...

  while (++tick % cycle) {
    offset = map2PI(tick);

    for (i = 0; i < stripsize; i++) {
      ang = map2PI(i) - offset;
      rsin = sin(ang);
      gsin = sin(2.0 * ang / 3.0 + map2PI(int(stripsize/6)));
      bsin = sin(4.0 * ang / 5.0 + map2PI(int(stripsize/3)));
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
  return PI*2.0*float(i) / float(strip.numPixels());
}

uint32_t Wheel(uint16_t WheelPos)
{
    byte r, g, b;
    switch(WheelPos / 128)
    {
        case 0:
        r = 127 - WheelPos % 128; // red down
        g = WheelPos % 128;       // green up
        b = 0;                    // blue off
        break;
        case 1:
        g = 127 - WheelPos % 128; // green down
        b = WheelPos % 128;       // blue up
        r = 0;                    // red off
        break;
        case 2:
        b = 127 - WheelPos % 128; // blue down
        r = WheelPos % 128;       // red up
        g = 0;                    // green off
        break;
    }
    return(strip.Color(r,g,b));
}

uint32_t GetColor(int c)
{
    switch(c) {
        case 0:
        return strip.Color(127,0,0);  //red
        case 1:
        return strip.Color(127,0,60);  
        case 2:
        return strip.Color(127,0,127); 
    case 3:  //orange
    return strip.Color(127,60,0);
    case 4:  //yellow
    return strip.Color(127,127,0);
    case 5:
    return strip.Color(127,127,60);
    case 6:
    return strip.Color(60,127,0);
    case 7:
    return strip.Color(60,127,127);
    case 8:
    return strip.Color(60,60,127);
    case 9:
    return strip.Color(60,90,60);
    case 10:
    return strip.Color(60,60,0);
    case 11:
        return strip.Color(0,0,127);  //blue
        case 12:
        return strip.Color(0,60,127);
        case 13:
        return strip.Color(0,127,127);
        case 14:
        return strip.Color(0,127,0);  //green
        case 15:
        return strip.Color(127,30,10);
        case 16:
        return strip.Color(25,80,100);
        case 17:
        return strip.Color(127,127,127);  //White
        case 18:
        int r, g, b;
        r = random(0, 50);
        g = random(40, 90);
        b = random(80, 128);
        return strip.Color(r,g,b);
        default:
        return strip.Color(0,0,0);
    }
}