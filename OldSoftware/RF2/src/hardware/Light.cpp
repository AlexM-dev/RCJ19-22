#include "Light.h"

LightSensor::LightSensor(){
  line = false;
  angle = 0;

  /*lineSerial = new SoftwareSerial(LINE_RX, LINE_TX);
  lineSerial->begin(115200);*/
  
  Log::info("Line", Serial1.available()? "Line connected" : "Line disconnected");
}

void LightSensor::update(){
  angle = getValueFromSensor();
}


int LightSensor::getAngle(){
  return angle;
}

bool LightSensor::isLine(){
  return line;
}

int LightSensor::getValueFromSensor(){

  if(Serial1.available()){
      int c = Serial1.read();
      line = false;
      if(c > 0) 
        line = true;
      angle = c;
  }
  else
    line = false;
  return angle;
}
