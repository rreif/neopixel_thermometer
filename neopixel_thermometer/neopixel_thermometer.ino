#include <Adafruit_NeoPixel.h>

const int PIN = 6;
const int testPin = 0;
//const float inputValue = 3.3;


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
const float pixelScale = (strip_size - 1) / 9;

void setup() {
  
  Serial.begin(9600);
  strip.setBrightness(5);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  showSingleDigits(analogRead(testPin));
  //delay(3000);
  //strip.setPixelColor(15, strip.Color(255, 0, 0));
  //strip.show();
}

void showSingleDigits(float testSignal) {

  // mapping measured data from sensor (testwise from poty) to the measurement range
  float input = map(testSignal, 0, 1023, 0, 5000);

  //transfer the input to a format to deal with, e.g. 2340 => 23.40
  float inputValue = input / 100;

  // cut off the decimal part of inputValue e.g. 23.4 => 23
  int integeredInputValue = (int) inputValue;

  // extract the first decimal digit
  int firstDecimalMeasured = integeredInputValue % 10; //  e.g. 3
  
  int scaleIndex = (integeredInputValue - firstDecimalMeasured) / 10; // e.g. (23 - 3)/10 => 2

  // re-construct the first decimal value of the measured value, e.g 3.4
  float inputFirstDecimal = inputValue - scaleIndex * 10;

  //transfer the fist decimal value of the measured value up to the ring size
  float mappedValue = inputFirstDecimal * pixelScale;

  // transform the scaled value finally to the according integer value to be displayed via neopixels
  int singleDigitValue = (int) mappedValue % 16;

  //set first digit (0°C indicator) always on 
  strip.setPixelColor(0, strip.Color(255, 255, 255));

  for(int i = strip.numPixels() - 1; i >= (int) (strip.numPixels() - singleDigitValue); i--) {
    strip.setPixelColor(i % strip.numPixels(), strip.Color(255, 255, 255));
    //Serial.println(i);
    strip.show();
    //delay(70);
  }
 for(short i = strip.numPixels() - singleDigitValue - 1; i > 0; i--) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    //delay(70);
 }
}

