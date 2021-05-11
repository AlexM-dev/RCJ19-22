#include "Cam.h"

CamSensor::CamSensor(){  ///  Blue   - 0
  Serial2.begin(115200); ///  Yellow - 1
  goal = 0;
}

void CamSensor::update(){

  if(Serial2.available() >= 13){
    char v = Serial2.read();
    if(v == '*'){
      for(int i = 0; i < 4; ++i){
        int a = Serial2.read() - '0';
        int b = Serial2.read() - '0';
        int c = Serial2.read() - '0';

        if(a < 0 || b < 0 || c < 0 || a > 9 || b > 9 || c > 9)
          continue;
        
        data[i] = a * 100;
        data[i] += b * 10;
        data[i] += c * 1;
      }
    }
  }

}

int CamSensor::getFormatedAngle(int ang){
  while(ang > 180)
    ang-=360;
  while(ang < -180)
    ang+=360;
  return ang;
}

void CamSensor::setGoal(int a){
  goal = a;  
}

int CamSensor::getYAngle(){
  return getFormatedAngle(data[0]);
}

int CamSensor::getBAngle(){
  return getFormatedAngle(data[2]);
}

int CamSensor::getYDist(){
  return data[1];
}

int CamSensor::getBDist(){
  return data[3];
}

int CamSensor::getCamDist(){
  return goal == 0? getBDist() : getYDist();
}

int CamSensor::getCamAngle(){
  return goal == 0? getBAngle() : getYAngle();
}

int CamSensor::getAnotherCamDist(){
  return goal == 0? getYDist() : getBDist();  
}

int CamSensor::getAnotherCamAngle(){
  return goal == 0? getYAngle() : getBAngle();
}