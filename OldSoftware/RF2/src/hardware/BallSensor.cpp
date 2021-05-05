#include "BallSensor.h"

BallSensor::BallSensor(){
  pinMode(BALL_CATCHED_LED_PIN, OUTPUT);
  digitalWrite(BALL_CATCHED_LED_PIN, HIGH);
  canSee = false;
  angle = 0;

  tsopSerial = new SoftwareSerial(TSOP_RX, TSOP_TX);
  tsopSerial->begin(115200);
  
}

void BallSensor::update(){
  angle = getValueFromSensor();
  if(abs(angle) == 179)
  {
    canSee = 0;
  }
  ballCatched = isBallCatched();
}

bool BallSensor::isBallCatched(){
  bool val = false;
  static  unsigned long long prev = millis();
  //Serial.println(analogRead(BALL_CATCHED_SENSOR_PIN));
  if(analogRead(BALL_CATCHED_SENSOR_PIN) > BALL_CATCHED_SENSOR_VALUE) {
    val = true;
    prev = millis();
  }
  else {
    if(millis() - prev < 1000){
      val = true;
    }
  }
  return val;
}

float BallSensor::getAngle(){
  return angle;
}

float BallSensor::getDistanse(){
  return distanse;
}

bool BallSensor::isCanSee(){
  return canSee;
}

bool BallSensor::isCatched(){
  return ballCatched;
}

int BallSensor::getValueFromSensor(){
  byte dt[2];
  static int erri = 0;


  if(tsopSerial->available() > sizeof(dt))
    if(tsopSerial->read() == 0xff){
      for(int i = 0; i < sizeof(dt); ++i)
        dt[i] = tsopSerial->read();
      erri = 0;

      if (dt[1] < 100)
        distanse = dt[1];
      distanse = distanse;

      canSee = true;
      if(dt[0] == 200 || distanse == 0){
        canSee = false;
        angle = 0;
        return angle;
      }

      int ang = (((dt[0]*2) + 315)%360) + 180;

      if(ang > 180)
      {
        ang = ang - 360;
        angle = ang;
        return angle;
      }
      if(ang < 180){
        ang = ang + 360;
        angle = ang;
        return angle;
      }
    } else erri++;
  if (erri > 5)
  {
    erri = 0;
    Log::warning("Movement","BallSensor Disconnected");
  }
  return angle;
}
