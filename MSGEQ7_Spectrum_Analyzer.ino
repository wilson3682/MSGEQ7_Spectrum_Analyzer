//
//This Code has been Modified and adapted to work on my MSGEQ7 Spectrum Visualizer from
//An equalizer controlled by The ESP8266 with the NodeMCU firmware(Ver 1.0) or arduino IDE C++ firmware(Ver 2.0),
//where the equalizer colors are controlled via WiFi.
//
//http://www.whatimade.today/graphic-equalizer-using-esp8266-msgeq7-ws2812/
//http://www.whatimade.today/part-2-spectrum-analyzer-with-esp8266-msgeq7-ws2812/
//https://github.com/amiravni/MSGEQ7_ESP8266_WS2812

#include <Adafruit_NeoPixel.h>
#include "classes.h"
octave myOctaves[7];
RGB colorTMP(0, 0, 0);
int long time_lapse = 0;
int long time_change = 0;
int effect = 0;

void setup() {
  delay(3000);
  strip.setBrightness(30);
  pinMode(STROBE_PIN , OUTPUT);
  pinMode(RESET_PIN , OUTPUT);
  digitalWrite(RESET_PIN , LOW);
  digitalWrite(STROBE_PIN , HIGH);
  strip.begin();
  strip.show();

  for (int i = 0; i < 7; i++) myOctaves[i].octaveInit(i);
  //  RGB color1(0, 255, 0);
  //  RGB color2(255, 255, 0);
  //  RGB color3(255, 0, 0);
  //  RGB color4(0, 0, 255);
  //  for (int i = 0; i < 7; i++) myOctaves[i].changeColorScheme(1, color1, color2, color3, 0.5, 1);
  //for (int i = 0; i < 7; i++) myOctaves[i].changeColorScheme(5, color3, color2, color3, 0.5, 1);
}

void loop() {
  refreshSpectrum();
  if (millis() - time_change > 12000) {   //code that establishes how often to change effect
    effect++;
    if (effect > 4) {
      effect = 0;
    }
    time_change = millis();
  }

  switch (effect) {
    case 0: {
        RGB color1(0, 255, 0);
        RGB color2(255, 255, 0);
        RGB color3(255, 0, 0);
        RGB color4(0, 0, 255);
        for (int i = 0; i < 7; i++) myOctaves[i].changeColorScheme(1, color4, color2, color1, 0.5, 1);
      }
      break;
    case 1:
      if (millis() - time_lapse > 15) {
        RGB color1(0, 255, 0);
        RGB color2(255, 255, 0);
        RGB color3(255, 0, 0);
        RGB color4(0, 0, 255);
        for (int i = 0; i < 7; i++) myOctaves[i].changeColorScheme(2, color4, color1, color3, 0.3, 1);
        time_lapse = millis();
      }
      break;
    case 2:
      if (millis() - time_lapse > 15) {
        RGB color1(0, 255, 0);
        RGB color2(255, 255, 0);
        RGB color3(255, 0, 0);
        RGB color4(0, 0, 255);
        for (int i = 0; i < 7; i++) myOctaves[i].changeColorScheme(3, color1, color2, color3, 0.5, 1);
        time_lapse = millis();
      }
      break;
    case 3:
      if (millis() - time_lapse > 15) {
        RGB color1(0, 255, 0);
        RGB color2(255, 255, 0);
        RGB color3(255, 0, 0);
        RGB color4(0, 0, 255);
        for (int i = 0; i < 7; i++) myOctaves[i].changeColorScheme(4, color1, color2, color3, 0.5, 1);
        time_lapse = millis();
      }
      break;
    case 4:
      if (millis() - time_lapse > 15) {
        RGB color1(0, 255, 0);
        RGB color2(255, 255, 0);
        RGB color3(255, 0, 0);
        RGB color4(0, 0, 255);
        for (int i = 0; i < 7; i++) myOctaves[i].changeColorScheme(5, color1, color2, color3, 0.5, 1);
        time_lapse = millis();
      }
      break;
  }
}

void refreshSpectrum() {
  digitalWrite(RESET_PIN , HIGH);
  digitalWrite(RESET_PIN , LOW);
  //for (int i = 0; i < 7; i++)  {  // Change it to reverse the Frequencies
  for (int i = 6; i >= 0; i--) {  // Change it to reverse the Frequencies
    myOctaves[6 - i].refreshBuffer();
    digitalWrite(STROBE_PIN , LOW);
    myOctaves[6 - i].readVal();
    digitalWrite(STROBE_PIN , HIGH);
    delay(0);
  }
  delay(numOfDelay);
  for (int i = 0; i < 7  ; i++)  {
    myOctaves[i].CalcLedsVal();
    myOctaves[i].drawLeds();
    delay(0);
  }
  strip.show();
}
