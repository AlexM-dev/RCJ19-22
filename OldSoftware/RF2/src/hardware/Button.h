#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "../Defines.h"


class Button {
public:
  Button();

  void init(int pin);
  void update();
  boolean isLongClick();
  boolean isClick();

private:
  int buttonPin;
  boolean pressed, afterClick;
  unsigned long previousMillis;

  void longClick();
  void click();
  boolean clickF, longClickF;
};

#endif
