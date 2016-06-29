#include <Adafruit_NeoPixel.h>

const int PIN = 6;
const float test_value = 8;


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
const float scale = strip_size / 9;

void setup() {
  
  Serial.begin(9600);
  strip.setBrightness(2);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  showSingleDigits();

}

void showSingleDigits() {
  float mappedValue = test_value*scale;
  //Serial.print();
  int singleDigitValue = (int) mappedValue;
  for(short i=strip.numPixels();i>strip.numPixels()-singleDigitValue;i--) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
    strip.show();
    delay(70);
  }
  strip.show();
}

