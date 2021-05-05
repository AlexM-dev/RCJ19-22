#include "Button.h"

Button::Button(){
  pressed = false;
  afterClick = false;
  clickF = false;
  longClickF = false;
}

void Button::init(int pin){
  previousMillis = millis();
  buttonPin = pin;
  pinMode(buttonPin,INPUT);
}


void Button::update(){

  if(!pressed && digitalRead(buttonPin) && millis() - previousMillis > AFTER_CLICK_TIME){
    previousMillis = millis();
    pressed = true;
    afterClick = false;
  }

  if(pressed && !afterClick && !digitalRead(buttonPin)) {
    unsigned long del = millis() - previousMillis;
    if(del >= MIN_CLICK_TIME && del < LONG_CLICK_TIME)
      click();
    else if(del >= LONG_CLICK_TIME)
      longClick();
    
    previousMillis = millis();
    afterClick = true;
    pressed = false;
  }

  /*if(afterClick && digitalRead(buttonPin) && millis() - previousMillis > AFTER_CLICK_TIME)
    afterClick = false;

  if(!pressed && !digitalRead(buttonPin)){
    if(!afterClick)
      pressed = true;
    previousMillis = millis();
  }

  if(pressed && digitalRead(buttonPin) && millis() - previousMillis > MIN_CLICK_TIME){
    pressed = false;
    click();
    afterClick = true;
  }

  if(pressed && !digitalRead(buttonPin) && millis() - previousMillis > LONG_CLICK_TIME){
    pressed = false;
    longClick();
    afterClick = true;
    previousMillis = millis();
  }*/
}

void Button::longClick(){
  longClickF = true;
}
void Button::click(){
  if(afterClick)
    return;
  clickF = true;
}

boolean Button::isLongClick(){
  if(!longClickF)
    return false;
  longClickF = false;
  return true;
} 
boolean Button::isClick(){
  if(!clickF)
    return false;
  clickF = false;
  return true;
}
