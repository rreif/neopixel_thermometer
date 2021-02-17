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

#define DELAYVAL 70 // Time (in milliseconds) to pause between pixels

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=NUMPIXELS; i>0; i--) { // For each pixel...
    if (i == pixels.numPixels()) {
      //offset for trailing pixels at start/end of the strip
      pixels.setPixelColor(pixels.numPixels() - 1, pixels.Color(1, 1, 1));
    } else if (i == (pixels.numPixels() - 1)) {
      pixels.setPixelColor(pixels.numPixels() - 1, pixels.Color(0, 0, 0));
    } else {
     pixels.setPixelColor(pixels.numPixels() - (i + 2), pixels.Color(0, 0, 0)); 
     pixels.setPixelColor(pixels.numPixels() - (i + 1), pixels.Color(1, 1, 1)); 
    }
    pixels.setPixelColor(pixels.numPixels() - i, pixels.Color(6, 6, 6));
    pixels.setPixelColor(pixels.numPixels() - (i - 1), pixels.Color(1, 1, 1));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}
