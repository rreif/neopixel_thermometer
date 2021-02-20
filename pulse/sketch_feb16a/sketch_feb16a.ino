// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 12 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 20 // Time (in milliseconds) to pause between pixels

#define MAX_BRIGHTNESS 32

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
}

void loop() {
  for(int single_pixel=NUMPIXELS; single_pixel>0; single_pixel--) { //iterate through all the single digits
    
    for(int i=MAX_BRIGHTNESS; i>=0; i--) {
      pixels.setPixelColor(pixels.numPixels() - single_pixel, pixels.Color(i, i, i));//fade out the first pixel

      //fade in the following pixel which in this case is the first one again
      if (single_pixel == 1) {
        pixels.setPixelColor(0, pixels.Color(MAX_BRIGHTNESS - i, MAX_BRIGHTNESS - i, MAX_BRIGHTNESS - i));
      } else {//fade in the following pixel
        pixels.setPixelColor(pixels.numPixels() - (single_pixel - 1), pixels.Color(MAX_BRIGHTNESS - i, MAX_BRIGHTNESS - i, MAX_BRIGHTNESS - i));
      }

      if (single_pixel == 4) {
        pixels.setPixelColor(pixels.numPixels() - (single_pixel - 1), pixels.Color(MAX_BRIGHTNESS - i, 0, 0));
      }
      if (single_pixel == 3) {
        pixels.setPixelColor(pixels.numPixels() - single_pixel, pixels.Color(i, 0, 0));
      }
      pixels.show();
      delay(DELAYVAL);
      }
  }
}
