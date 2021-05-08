#include "Movement.h"

void Movement::initilizeMotors() {
  //Init Vars
  tSpeed = 0;
  cSpeed = 0;
  rAngle = 0;
  oldErr = 0;
  targetAngle = 0;
  dirAngle = 0;
  rotationK = 0;
  zeroAngle = 0;
  rTime = micros();
  I = 0;
  gyroEn = true;
  canMove = false;
  Serial3.begin(115200);

  //Init Pins
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);
  pinMode(M3_IN1, OUTPUT);
  pinMode(M3_IN2, OUTPUT);
  pinMode(M4_IN1, OUTPUT);
  pinMode(M4_IN2, OUTPUT);

  Log::info("Movement","Init Complete");
  Log::info("Movement", Serial3.available()? "Gyro connected" : "Gyro disconnected");
  
  stopMotors();
}

//Private functions
void Movement::runMotor(int motorIndex, int pwmSpeed) {
  if(!canMove){
    stopMotors();
    return;
  }

  //True Forward; False backward
  boolean dir = true;
  if (pwmSpeed < 0) {
    dir = false;
    pwmSpeed = -pwmSpeed;
  }

  //Switch for each motor
  switch (motorIndex) {
    case 1:
      analogWrite(M1_IN1, dir ? pwmSpeed : 0);
      analogWrite(M1_IN2, dir ? 0 : pwmSpeed);
      break;

    case 2:
      analogWrite(M2_IN1, dir ? pwmSpeed : 0);
      analogWrite(M2_IN2, dir ? 0 : pwmSpeed);
      break;

    case 3:
      analogWrite(M3_IN1, dir ? pwmSpeed : 0);
      analogWrite(M3_IN2, dir ? 0 : pwmSpeed);
      break;

    case 4:
      analogWrite(M4_IN1, dir ? pwmSpeed : 0);
      analogWrite(M4_IN2, dir ? 0 : pwmSpeed);
      break;
  }
}

void Movement::updateRotationK() {
  if (Serial3.available()) {
    rAngle = AngleUtils::getFormatedAngle(Serial3.read() * 2);

    int err = targetAngle - rAngle;
    if (err > 180) err-=360;
    else if (err < -180) err+=360;
    I += err * (micros() - rTime) / 1000;

    if(abs(I) > 0)
      I = 0;
    rotationK = (err * ROT_K) + ((err - oldErr) * ROT_D); //+ I * ROT_I;
    if(abs(err) < 5)
      rotationK = 0;

    oldErr = err;
    rTime = micros();
  }

  
  if (!gyroEn){
    rotationK = 0;
    return;
  }

  if (rotationK > MAX_ROTATION_K)
    rotationK = MAX_ROTATION_K;
  if (rotationK < -MAX_ROTATION_K)
    rotationK = -MAX_ROTATION_K;
  if (rotationK > 0 && rotationK < MIN_ROTATION_K)
    rotationK = MIN_ROTATION_K;
  if (rotationK < 0 && rotationK > -MIN_ROTATION_K)
    rotationK = -MIN_ROTATION_K;
}


//Setters
void Movement::setRotationByGyro() {
  zeroAngle = AngleUtils::getFormatedAngle(rAngle);
  targetAngle = zeroAngle;
}
void Movement::setRotation(int a) {

  targetAngle = AngleUtils::getFormatedAngle(a + zeroAngle);
  
}
void Movement::setDirection(int a) {
  dirAngle = -AngleUtils::getFormatedAngle(a);
}
void Movement::setGyroEnabled(bool enabled) {
  gyroEn = enabled;
}
void Movement::setSpeed(int s) {
  tSpeed = s;
}
void Movement::setCanMove(bool can){
  canMove = can;
}

//Getters
int Movement::getTargetRobotAngle(){
  return targetAngle;
}
int Movement::getRobotAngle(){
  return rAngle;
}
int Movement::getSpeed(){
  return tSpeed;
}
int Movement::getDirection(){
  return dirAngle;
}
bool Movement::isGyroEnabled(){
  return gyroEn;
}
bool Movement::isCanMove(){
  return canMove;
}

//Move MoveCommands
void Movement::moveM(int s, int a) {
  //Save cur speed
  tSpeed = s;
  dirAngle = a;

  a = a + (targetAngle - rAngle);

  if((cSpeed + rotationK) > 200){
    cSpeed -= ((cSpeed + rotationK) - 200);
  }

  //Get speed of motors
  runMotor(4, cSpeed * cos(radians(a + 45)) + rotationK);
  runMotor(1, cSpeed * cos(radians(a + 135)) + rotationK);
  runMotor(2, cSpeed * cos(radians(a + 225)) + rotationK);
  runMotor(3, cSpeed * cos(radians(a + 315)) + rotationK);
}

void Movement::stopMotors() {
  analogWrite(M1_IN1, 0);
  analogWrite(M1_IN2, 0);
  analogWrite(M2_IN1, 0);
  analogWrite(M2_IN2, 0);
  analogWrite(M3_IN1, 0);
  analogWrite(M3_IN2, 0);
  analogWrite(M4_IN1, 0);
  analogWrite(M4_IN2, 0);
}

void Movement::stop() {
  setSpeed(0);
}

//Runtime functions
void Movement::update() {
  if(abs(tSpeed - cSpeed) > VELOSITY_SPEED){
    if(tSpeed > cSpeed)
      cSpeed += VELOSITY_SPEED;
    else if(tSpeed < cSpeed)
      cSpeed -= VELOSITY_SPEED;
  } else cSpeed = tSpeed;

  //Update rotationK by Gyro
  updateRotationK();
  //moveD(driblerEn);
  //Run Motors
  moveM(tSpeed, dirAngle);
}