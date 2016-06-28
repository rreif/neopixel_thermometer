#include <Adafruit_NeoPixel.h>

const int PIN = 6;
const float test_value = 4;


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.setBrightness(2);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  showSingleDigits();

}

void showSingleDigits() {
  int value = map(test_value, 0, 9, 1, 2*strip.numPixels());
  for(short i=strip.numPixels();i>strip.numPixels()-value;i--) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
    strip.show();
    delay(70);
  }
  strip.show();
}

