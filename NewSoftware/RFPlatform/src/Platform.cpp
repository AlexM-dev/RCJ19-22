#include "Platform.h"

Platform::Platform(DevicesController *controller, Vec2 *vec)
{
    devicesController = controller;
    moveVector = vec;
    // Get Gyro from device controller
    gyro = devicesController->getDevice<Gyro*>(GYRO_DEVICE_ID);

    Log::nl();
    Log::success("Platform created");
}

int Platform::getRobotAngle()
{
    if(gyro != nullptr)
        return gyro->getAngle();
    else
        return 0;
}

void Platform::init()
{
    Log::info("     Initing vars and outs...");
    // Movement vars init
    currentSpeed = 0;
    canMove = false;
    // Stabilization vars init
    stabilizationEnabled = true;
    targetAngle = 0;
    rotationOldError = 0;
    rotationI = 0;
    rotationK = 0;
    rotationTime = 0;
    // Set all pins to OUTPUT
    pinMode(M1_IN1, OUTPUT);
    pinMode(M1_IN2, OUTPUT);
    pinMode(M2_IN1, OUTPUT);
    pinMode(M2_IN2, OUTPUT);
    pinMode(M3_IN1, OUTPUT);
    pinMode(M3_IN2, OUTPUT);
    pinMode(M4_IN1, OUTPUT);
    pinMode(M4_IN2, OUTPUT);
}

void Platform::runMotor(int motorIndex, int pwmSpeed) {
  //  true Forward; false backward
  bool dir = true;
  if (pwmSpeed < 0) {
    dir = false;
    pwmSpeed = -pwmSpeed;
  }

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

void Platform::updateRotation()
{
    if(!stabilizationEnabled || !canMove) 
    {
        rotationK = 0;
        return;
    }

    int err = Utils::getFormatedAngle(targetAngle - getRobotAngle());
    rotationI += err * (micros() - rotationTime) / 1000;

    // This shit is always true.... WTF????? 
    if(abs(rotationI) > I_MAX)   
      rotationI = 0;

    // Compute rotationK and limit it
    rotationK = (err * ROT_K) + ((err - rotationOldError) * ROT_D) + rotationI * ROT_I; // OK, but....
    if(abs(err) < 5) // This part stops super slow rotation
      rotationK = 0;
    rotationK = Utils::mirroredValueLimit(rotationK, MIN_ROTATION_K, MAX_ROTATION_K);

    rotationOldError = err;
    rotationTime = micros();
}

void Platform::updateSpeed()
{
    if(!canMove)
    {
      currentSpeed = 0;
      return;
    }

    int speed = moveVector->getSpeed();
    if(speed + rotationK > MAX_SPEED)
        speed = MAX_SPEED - rotationK;

    int maxVelocity = MAX_VELOCITY;
    if((speed > 0 && currentSpeed < 0) || (speed < 0 && currentSpeed > 0))
      maxVelocity *= 4;

    if(abs(speed - currentSpeed) > MIN_VELOCITY)
    {
        if(currentSpeed < speed)
            currentSpeed += map(speed - currentSpeed, 0, MAX_SPEED, MIN_VELOCITY, maxVelocity);
        else if(currentSpeed > speed)
            currentSpeed -= map(currentSpeed - speed, 0, MAX_SPEED, MIN_VELOCITY, maxVelocity);
    } else currentSpeed = speed;
}

void Platform::updateMotors()
{
    int angle = moveVector->getAngle();
    angle = angle + (targetAngle - getRobotAngle());
    int speed = currentSpeed;
    // Disable movement for quick rotation
    if(abs(rotationK) > QUICK_ROTATION_SPEED)
        speed = 0;
    // Set motor speeds
    runMotor(4, speed * cos(radians(-angle + 45 )) + rotationK);
    runMotor(1, speed * cos(radians(-angle + 135)) + rotationK);
    runMotor(2, speed * cos(radians(-angle + 225)) + rotationK);
    runMotor(3, speed * cos(radians(-angle + 315)) + rotationK);
    // Debug output
    // Log::info("Angle: " + String(moveVector->getAngle()) + " Speed: " + String(moveVector->getSpeed()));
}

void Platform::update() 
{
    updateRotation();
    updateSpeed();
    updateMotors();
}

void Platform::setTargetAngle(int angle)
{
    targetAngle = angle;
}
bool Platform::isCanMove()
{
    return canMove;
}
bool Platform::isStabilizationEnabled()
{
    return stabilizationEnabled;
}
void Platform::setCanMove(bool can){
  canMove = can;
}