#include "SoftwareSerial.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN    9
#define LED_COUNT  16

SoftwareSerial mySerial(7, 8);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);

int brightness = 50;
int LEDMode = 2;
char cmd;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(brightness);
}

void loop() {
  // Fill along the length of the strip in various colors...
  if (mySerial.available()){
    cmd = mySerial.read();
    switch(cmd){
      case '0':
        LEDMode = 0;
        break;
      case '1':
        LEDMode = 1;
        break;
      case '2':
        LEDMode = 2;
        break;
      case '3':
        LEDMode = 3;
        break;
    }
  }
  if (LEDMode == 0){
    colorWipe(strip.Color(255,   0,   0)     , 50); // Red
    colorWipe(strip.Color(  0, 255,   0)     , 50); // Green
    colorWipe(strip.Color(  0,   0, 255)     , 50); // Blue
    colorWipe(strip.Color(  0,   0,   0, 255), 50); // True white (not RGB white)
  } else if (LEDMode == 1){
    pulseWhite(5);
  } else if (LEDMode == 2){
    rainbow(3, 1);
  } else if (LEDMode == 3){
    randomColor();
  }
}

void readBrightness(){
  int value = analogRead(A0);
  brightness = map(value, 15, 1023, 0, 255);
  
  if (brightness < 0){
    brightness = 0;
  } else if (brightness > 255){
    brightness = 255;
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    readBrightness();
    strip.setBrightness(brightness);
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

//void whiteOverRainbow(int whiteSpeed, int whiteLength) {
//
//  if(whiteLength >= strip.numPixels()) whiteLength = strip.numPixels() - 1;
//
//  int      head          = whiteLength - 1;
//  int      tail          = 0;
//  int      loops         = 3;
//  int      loopNum       = 0;
//  uint32_t lastTime      = millis();
//  uint32_t firstPixelHue = 0;
//
//  for(;;) { // Repeat forever (or until a 'break' or 'return')
//    for(int i=0; i<strip.numPixels(); i++) {  // For each pixel in strip...
//      if(((i >= tail) && (i <= head)) ||      //  If between head & tail...
//         ((tail > head) && ((i >= tail) || (i <= head)))) {
//        strip.setPixelColor(i, strip.Color(0, 0, 0, 255)); // Set white
//      } else {                                             // else set rainbow
//        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
//        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
//      }
//    }
//
//    readBrightness();
//    strip.setBrightness(brightness);
//    strip.show(); // Update strip with new contents
//    // There's no delay here, it just runs full-tilt until the timer and
//    // counter combination below runs out.
//
//    firstPixelHue += 40; // Advance just a little along the color wheel
//
//    if((millis() - lastTime) > whiteSpeed) { // Time to update head/tail?
//      if(++head >= strip.numPixels()) {      // Advance head, wrap around
//        head = 0;
//        if(++loopNum >= loops) return;
//      }
//      if(++tail >= strip.numPixels()) {      // Advance tail, wrap around
//        tail = 0;
//      }
//      lastTime = millis();                   // Save time of last movement
//    }
//  }
//}

void pulseWhite(uint8_t wait) {
  for(int j=0; j<256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
    readBrightness();
    strip.setBrightness(brightness);
    strip.show();
    delay(wait);
  }

  for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
    readBrightness();
    strip.setBrightness(brightness);
    strip.show();
    delay(wait);
  }
}

void rainbow(int wait, int rainbowLoops) {

  for(uint32_t firstPixelHue = 0; firstPixelHue < rainbowLoops*65536;
    firstPixelHue += 256) {

    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...

      uint32_t pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());

      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue, 255,
        255)));
    }
    readBrightness();
    strip.setBrightness(brightness);
    strip.show();
    delay(wait);
  }
}

void randomColor(){
  uint32_t randomPixelHue = random(0, 65536);
  int i = random(0, strip.numPixels());
  uint32_t pixelHue = randomPixelHue + (i * 65536L / strip.numPixels());
  int S = random(0, 256);
  int V = random(0, 256);
//  int G = random(0, 256);
//  int B = random(0, 256);
  strip.fill(strip.gamma32(strip.ColorHSV(pixelHue, S, V)));
  readBrightness();
  strip.setBrightness(brightness);
  strip.show();
  delay(100);
//  delay(500);
}
