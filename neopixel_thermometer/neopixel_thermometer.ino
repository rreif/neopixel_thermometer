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
  strip.setBrightness(6);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'  
}

int lastDisplayedValue = 0;
int currentDisplayValue = 0;

void loop() {
  currentDisplayValue = getCurrentDisplayValue(analogRead(testPin));
  showSingleDigits();
  delay(3000);
}

int getCurrentDisplayValue(float sensorValue) {
  // mapping measured data from sensor (testwise from poty) to the measurement range
  float input = map(sensorValue, 0, 1023, -2000, 5000);

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
  return singleDigitValue;
}

void showSingleDigits() {

  //set first digit (0°C indicator) always on 
  strip.setPixelColor(0, strip.Color(255, 255, 255));

  //show lastDisplayedValue
  // for positive values spin clockwise
  if (lastDisplayedValue >= 0) {
    for(short i = strip.numPixels() - 1; i >= (short) (strip.numPixels() - lastDisplayedValue); i--) {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
    for(short i = strip.numPixels() - lastDisplayedValue - 1; i > 0; i--) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
  // when it´s getting freezing spin non-clockwise
  else {
    for(short i = 1; i <= abs(lastDisplayedValue); i++) {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
    for(short i = abs(lastDisplayedValue) + 1; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    } 
  }
  strip.show();
  
  //Serial.println(lastDisplayedValue);
  //Serial.println(currentDisplayValue);
  if (lastDisplayedValue != currentDisplayValue) {
    transitionToCurrent();
    lastDisplayedValue = currentDisplayValue;
  }
}

void transitionToCurrent() {
  int difference = lastDisplayedValue - currentDisplayValue;
  
  //we are on the positive side of the ring
  if ((lastDisplayedValue >= 0) && (currentDisplayValue >= 0)) {
    //we need to show less digits
    if (difference > 0) {
      for(difference; difference > 0; difference--) {
        for(short i = 255; i >= 0; i--){
          strip.setPixelColor(strip.numPixels() - currentDisplayValue - difference, strip.Color(i, i, i));
          strip.show();  
        }
      }
    }
    //we need to show more digits
    else {
      for(difference; difference <= 0; difference++) {
        for(short i = 0; i <= 255; i++){
          strip.setPixelColor(strip.numPixels() - currentDisplayValue + abs(difference), strip.Color(i, i, i));
          strip.show();  
        }
      }
    }
  }
  //we are on the negative side of the ring
  else if ((lastDisplayedValue < 0) && (currentDisplayValue < 0)) {
    if (difference < 0) {
      //Serial.println(difference);
      for(difference; difference < 0; difference++) {
        Serial.println(currentDisplayValue);
        Serial.println(lastDisplayedValue);
        Serial.println(difference);
        for(short i = 255; i >= 0; i--){
          strip.setPixelColor(abs(currentDisplayValue) - difference, strip.Color(i, i, i));
          strip.show(); 
        }
      }
    }
  }
}

