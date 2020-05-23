uint32_t effTimer;
byte ind;

void effectsTick() {
  // if (!dawnFlag)
  {
    if (ONflag && millis() - effTimer >= ((currentMode < 5 || currentMode > 13) ? modes[currentMode].speed : 50) ) {
      effTimer = millis();
      switch (currentMode) {
        case 0: fillAll(CRGB::Green);
          break;
        case 1: fillAll(CRGB::Red);
          break;
        case 2: rainbowVertical();
          break;
        case 3: rainbowHorizontal();
          break;
        case 4: colorsRoutine();
          break;
        case 5: fillAll(CRGB::MediumVioletRed);
          break;
        case 6: fillAll(CRGB::Yellow);
          break;
        case 7: fillAll(CRGB::LightYellow);
          break;
        case 8: fillAll(CRGB::HotPink);
          break;
        case 9: fillAll(CRGB::Indigo);
          break;
        case 10: fillAll(CRGB::MediumTurquoise);
          break;
        case 11: fillAll(CRGB::OrangeRed);
          break;
        case 12: fillAll(CRGB::LimeGreen);
          break;
        case 13: fillAll(CRGB::Moccasin);
          break;
        case 14: fillAll(CRGB::PowderBlue);
          break;
        case 15: ColorCHSVLamp(192);
          break;
        case 16: fillAll(CRGB::OliveDrab);
          break;
        case 17: ColorCHSVLamp(224);
          break;
      }
      switch (numHold) {    // индикатор уровня яркости/скорости/масштаба
        case 1:
          ind = sqrt(modes[currentMode].brightness + 1);
          for (byte y = 0; y < HEIGHT ; y++) {
            if (ind > y) drawPixelXY(0, y, CHSV(10, 255, 255));
            else drawPixelXY(0, y,  0);
          }
          break;
        case 2:
          ind = sqrt(modes[currentMode].speed - 1);
          for (byte y = 0; y <= HEIGHT ; y++) {
            if (ind <= y) drawPixelXY(0, 15 - y, CHSV(100, 255, 255));
            else drawPixelXY(0, 15 - y,  0);
          }
          break;
        case 3:
          ind = sqrt(modes[currentMode].scale + 1);
          for (byte y = 0; y < HEIGHT ; y++) {
            if (ind > y) drawPixelXY(0, y, CHSV(150, 255, 255));
            else drawPixelXY(0, y,  0);
          }
          break;

      }
      FastLED.show();
    }
  }
}

void changePower() {    // плавное включение/выключение
  if (ONflag) {
    effectsTick();
    for (int i = 0; i < modes[currentMode].brightness; i += 8) {
      FastLED.setBrightness(i);
      delay(1);
      FastLED.show();
    }
    FastLED.setBrightness(modes[currentMode].brightness);
    delay(2);
    FastLED.show();
  } else {
    effectsTick();
    for (int i = modes[currentMode].brightness; i > 8; i -= 8) {
      FastLED.setBrightness(i);
      delay(1);
      FastLED.show();
    }
    FastLED.clear();
    delay(2);
    FastLED.show();
  }
}
