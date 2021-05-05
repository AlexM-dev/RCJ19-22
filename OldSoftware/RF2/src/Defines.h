#ifndef DEFINES_H
#define DEFINES_H

#define BASE_SPEED 50 //скорость чтоб отдельно ее везде не менять

//Control Elements
#define BUTTON_PIN1 A10
#define BUTTON_PIN2 A10
#define BUTTON_PIN3 A10


//Movement Settings
#define M1_IN1 6
#define M1_IN2 4
#define M2_IN1 8
#define M2_IN2 10
#define M3_IN1 9
#define M3_IN2 7 
#define M4_IN1 5 
#define M4_IN2 3 
#define DRIBBLER_PIN 12

//Speed Settings
#define ROT_K 0.4
#define ROT_D 0.55
#define ROT_I 0.00035
#define I_MAX 3000
#define MAX_ROTATION_K 200
#define MIN_ROTATION_K 15
#define MAX_SPEED 200
#define ballFollowK 1.3
#define VELOSITY_SPEED 5
#define D_VELOSITY_SPEED 15

//Ball Sensor Settings
#define BALL_CATCHED_SENSOR_PIN A5
#define BALL_CATCHED_LED_PIN 50
#define BALL_CATCHED_SENSOR_VALUE 950

//SONARS PINS
#define LEFT_SONAR_PIN A6
#define RIGHT_SONAR_PIN A2
#define BOTTOM_SONAR_PIN A4
#define GOAL_DISTANSE 45

//Goalkeaper Settings
#define GK_SPEED 60
#define GK_MIN_SPEED 40
#define GK_MIN_BALL_DIST 75
#define GK_BALL_ANG 15
#define GO_ON_BALL_TIME 1000

//Button Settings
#define LONG_CLICK_TIME 1000
#define MIN_CLICK_TIME 50
#define AFTER_CLICK_TIME 200

#define ASCIIConvert 48

#define TSOP_RX 62
#define TSOP_TX 46

#define LINE_RX 64
#define LINE_TX 44

#define CAM_RX 44
#define CAM_TX 42

#define MAX_PPM 1900
#define MIN_PPM 1100
#define MID_PPM 1500
#define DriblerOn 130

#define KICK_DIST 20


#define maxDistFromGoaltoRobot 30
#define minDistFromGoaltoRobot 20
#define maxAngle 120
#define minDist 14
#define coordsYConst 0

#endif
