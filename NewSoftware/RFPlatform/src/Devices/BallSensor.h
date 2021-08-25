#pragma once

#include "Device.h"
#include "../Defines.h"
#include "../Utils/Log.h"
#include <SoftwareSerial.h>

class BallSensor : public Device
{
private:
    SoftwareSerial *tsopSerial;
    int angle;
    int distanse;
    bool canSee;
    bool catched;
public:
    BallSensor(int id) : Device(id)
    { 
        pinMode(BALL_CATCHED_LED_PIN, OUTPUT);
        digitalWrite(BALL_CATCHED_LED_PIN, HIGH);

        canSee = false;
        catched = false;
        angle = 0;
        distanse = 0;

        tsopSerial = new SoftwareSerial(TSOP_RX, TSOP_TX);
    }
    ~BallSensor() { }

    int updateDelay() override
    {
        return 10;  // Refresh every 10ms
    }

    void collectData() override
    { 
        if(analogRead(BALL_CATCHED_SENSOR_PIN) > BALL_CATCHED_SENSOR_VALUE)
            catched = true;
        else 
            catched = false;

        byte dt[2];
        if(tsopSerial->available() > sizeof(dt))
            if(tsopSerial->read() == 0xff)
            {
                for(int i = 0; i < sizeof(dt); ++i)
                    dt[i] = tsopSerial->read();

                if (dt[1] < 100)
                    distanse = dt[1];

                canSee = true;
                if(dt[0] == 200 || distanse == 0)
                {
                    canSee = false;
                    angle = 0;
                }

                int ang = (((dt[0]*2) + 315)%360) + 180;
                angle = Utils::getFormatedAngle(ang);
            }
    }


    void connectToDevice() override
    {
        tsopSerial->begin(115200);
    }
    bool isConnected() override 
    {
        return tsopSerial->isListening();
        // return false;
    }

    int getAngle()
    {
        return angle;
    }
    int getDistanse()
    {
        return distanse;
    }
    bool isCanSee()
    {
        return canSee;
    }
    bool isCatched()
    {
        return catched;
    }
};
