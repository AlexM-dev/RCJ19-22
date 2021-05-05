#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include "math.h"
#include "../Defines.h"
#include "../libs/Log.h"
#include "../libs/AngleUtils.h"



class Movement{
public:
  //Init
  void initilizeMotors();

  //Runtime functions
  void update();

  //MoveCommands
  void moveM(int s, int a);
  void stop();

  //Setters
  void setRotationByGyro();
  void setRotation(int a);
  void setDirection(int a);
  void setGyroEnabled(bool enabled);
  void setSpeed(int s);
  void setCanMove(bool can);

  //Getters
  int getTargetRobotAngle();
  int getRobotAngle();
  int getSpeed();
  int getDirection();
  bool isGyroEnabled();
  bool isCanMove();
  void runMotor(int motorIndex, int pwmSpeed);

private:
  //Move
  int tSpeed, cSpeed;
  int dirAngle;
  int oldErr;
  //RotateRobot
  int rAngle, targetAngle, zeroAngle;
  int rotationK;
  unsigned long rTime;
  bool gyroEn, canMove;
  double I = 0;

  //Private functions
  void updateRotationK();
  
  void stopMotors();
};

#endif
