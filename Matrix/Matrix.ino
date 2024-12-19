#include <FastLED.h>

#define NUM_LEDS 256
#define width 16
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setBrightness(60);
  FastLED.clear();
  FastLED.show();
  pixel(0, 0, CRGB::Blue, 1);
  pixel(0, 1, CRGB::Green, 1);
  pixel(1, 0, CRGB::Red, 1);
}

void pixel(byte x, byte y, CRGB Color, bool shower) {
  byte index = y % 2 == 1 ? y * width + (width - 1 - x) : y * width + x;
  leds[index] = Color;
  if (shower) FastLED.show();
}

void rectangle(byte x1, byte y1, byte x2, byte y2, CRGB Color, boolean filled = 1) {
  if(filled){
    byte dx = x2 - x1;
    byte dy = y2 - y1;
    byte sign = dy/abs(dy);
    for(byte y = y1; y < y2 + sign; y += sign){
      line(x1, y, x2, y, Color);
    }
  }
  else{
    line(x1, y1, x1, y2, Color);
    line(x1, y2, x2, y2, Color);
    line(x2, y2, x2, y1, Color);
    line(x2, y1, x1, y1, Color);
  }
 
}

void line(int x1, int y1, int x2, int y2, CRGB color) {
  int dx = x2 - x1;
  int dy = y2 - y1;
  float ky = (float) (y2 - y1) / (x2 - x1);
  if (abs(dx) >= abs(dy)) {
    int yn;
    for (int x = 0; x != (dx + dx / abs(dx)); x += dx / abs(dx)) {
      yn = y1 + x * dy / dx;
      pixel(x1 + x, yn, color, 0);
    }
  }
  else {
    int xn;
    for (int y = 0; y != (dy + dy / abs(dy)); y += dy / abs(dy)) {
      xn = x1 + y * dx / dy;
      pixel(xn, y1 +y, color, 0);
    }
  }
  FastLED.show();
}

void download_animation(){
  delay(500);
  line(5, 8, 7, 10, CRGB::Red);
  delay(500);
  line(7, 10, 9, 8, CRGB::Green);
  delay(500);
  line(9, 8, 7, 6, CRGB::Blue);
  delay(500);
  line(7, 6, 5, 8, CRGB::White);
  delay(500);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  rectangle(3, 3, 7, 15, CRGB::Green, 0);
}
