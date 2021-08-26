#pragma once

// Core defines
#define ACTIONS_STACK_SIZE 10


// Goals 1 BLUE, 2 YELLOW
#define GOALS 2

// Buttons IDs
#define BUTTON1_ID 0
#define BUTTONS_COUNT 1
#define BUTTON_LONG_CLICK_DELAY 600
#define BUTTON_REFRESH_RATE 15


// Ball sensor settings
#define BALL_CATCHED_SENSOR_PIN A5
#define BALL_CATCHED_LED_PIN 50
#define BALL_CATCHED_SENSOR_VALUE 750
#define TSOP_RX 62
#define TSOP_TX 46

// Devices IDs
#define GYRO_DEVICE_ID 0
#define BALL_DEVICE_ID 1
#define LINE_DEVICE_ID 2
#define DRIB_DEVICE_ID 3
#define KICK_DEVICE_ID 4
#define CAM_DEVICE_ID 5
#define DEVICES_COUNT 6

// Timers settings
#define MAX_TIMERS_COUNT 5

// Platform Settings
//   Speed Settings 
#define BASE_SPEED 150
#define MAX_SPEED 250
#define MAX_VELOCITY 10
#define MIN_VELOCITY 1
#define MAX_ROTATION_K 100
#define MIN_ROTATION_K 15
#define QUICK_ROTATION_SPEED 50   

//    Rotation Settings
#define ROT_K 0.52  // #define ROT_K 0.52
#define ROT_D 13.4    // #define ROT_D 5.3
#define ROT_I 0.0007
#define I_MAX 3000

//    Motors pins
#define M1_IN1 6
#define M1_IN2 4
#define M2_IN1 8
#define M2_IN2 10
#define M3_IN1 9
#define M3_IN2 7 
#define M4_IN1 5 
#define M4_IN2 3 

//    Sonars pins
#define LEFT_SONAR_PIN A6
#define RIGHT_SONAR_PIN A2
#define BOTTOM_SONAR_PIN A4

//   Dribbler settings
#define DRIBBLER_PIN 12
#define MID_PWM 1500