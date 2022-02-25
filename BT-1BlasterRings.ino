#include <Arduino.h>
#include "NeoPatterns.h"

// Which pin on the Arduino is connected to the NeoPixels?

void PatternHandler(NeoPatterns *aLedsPtr);

#define PIN_NEOPIXEL_ALL        6

NeoPatterns allPixel = NeoPatterns(40, PIN_NEOPIXEL_ALL, NEO_GRB + NEO_KHZ800, &PatternHandler);
NeoPatterns ring1 = NeoPatterns(&allPixel, 0, 8, true, &PatternHandler);
NeoPatterns ring2 = NeoPatterns(&allPixel, 8, 8, true, &PatternHandler);
NeoPatterns ring3 = NeoPatterns(&allPixel, 16, 8, true, &PatternHandler);
NeoPatterns ring4 = NeoPatterns(&allPixel, 24, 8, true, &PatternHandler);
NeoPatterns ring5 = NeoPatterns(&allPixel, 32, 8, true, &PatternHandler);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  ring1.begin();
  ring2.begin();
  ring3.begin();
  ring4.begin();
  ring5.begin();

  ring1.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE;
  ring2.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE;
  ring3.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE;
  ring4.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE;
  ring5.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE;

  delay(300); // to avoid partial patterns at power up

  ring1.ColorWipe(COLOR32_PURPLE, 50);
  ring2.ColorWipe(COLOR32_RED, 50);
  ring3.ColorWipe(COLOR32_GREEN, 50);
  ring4.ColorWipe(COLOR32_BLUE, 50);
  ring5.ColorWipe(COLOR32_RED, 50);

//    bar24.ScannerExtended(COLOR32_BLUE, 5, 50, 1,
//            FLAG_SCANNER_EXT_ROCKET | FLAG_SCANNER_EXT_VANISH_COMPLETE | FLAG_SCANNER_EXT_START_AT_BOTH_ENDS);


  Serial.println("started");
}

void loop() {
  // put your main code here, to run repeatedly:
  ring1.update();
  ring2.update();
  ring3.update();
  ring4.update();
  ring5.update();

}

void PatternHandler(NeoPatterns *aLedsPtr) {
      static int8_t sState = 0;

    switch (sState) {
    case 0:
        aLedsPtr->ColorWipe(COLOR32_RED_HALF, 50);
        break;
    case 1:
        aLedsPtr->Delay(500);
        break;
    case 2:
        aLedsPtr->Heartbeat(COLOR32_GREEN, 50, 0);
        break;
    case 3:
        aLedsPtr->Delay(500);
        break;
    case 4:
        aLedsPtr->RainbowCycle(50, DIRECTION_UP);
        break;
    case 5:
        aLedsPtr->RainbowCycle(50, DIRECTION_DOWN);
        break;
    case 6:
        aLedsPtr->Delay(400);
        break;
    case 7:
        aLedsPtr->Fire(20, 400); // OK Fire(30, 260)is also OK
        break;
    case 8:
        // switch to random
        initMultipleFallingStars(aLedsPtr, COLOR32_WHITE_HALF, 7, 30, 3, &allPatternsRandomHandler);
        sState = -1; // Start from beginning
        break;
    default:
        Serial.println("ERROR");
        break;
    }

    Serial.print("PatterHandler: Pin=");
    Serial.print(aLedsPtr->getPin());
    Serial.print(" Length=");
    Serial.print(aLedsPtr->numPixels());
    Serial.print(" ActivePattern=");
    aLedsPtr->printPatternName(aLedsPtr->ActivePattern, &Serial);
    Serial.print("|");
    Serial.print(aLedsPtr->ActivePattern);
    Serial.print(" State=");
    Serial.println(sState);

    sState++;
}
