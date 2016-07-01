#include <Adafruit_NeoPixel.h>

const int PIN = 6;
const float inputValue = 10.5;


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

const float strip_size = (float) strip.numPixels();
const float pixelScale = strip_size / 10;

void setup() {
  
  Serial.begin(9600);
  strip.setBrightness(5);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  showSingleDigits();

}

void showSingleDigits() {
  
  int integeredInputValue = (int) inputValue; //e.g. 23.4 => 23
  int moduloRest = integeredInputValue % 10; //  e.g. 3
  int scaleIndex = (integeredInputValue - moduloRest) / 10; // e.g. (23 - 3)/10 => 2
  float reducedInputValue = inputValue - scaleIndex * 10;
  float mappedValue = reducedInputValue * pixelScale;
  int singleDigitValue = (int) mappedValue;
  float decimalValue = mappedValue - singleDigitValue;
  
  for(short i = strip.numPixels(); i > strip.numPixels() - singleDigitValue - 1; i--) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
    strip.show();
    delay(70);
  }
  strip.setPixelColor(strip.numPixels() - singleDigitValue - 1, strip.Color(255 * decimalValue, 255 * decimalValue, 255 * decimalValue));
  strip.show();
}

