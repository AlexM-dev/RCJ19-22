#pragma once

#include "Device.h"
#include "../Defines.h"
#include "../Utils/Log.h"
#include <Servo.h>

class Dribbler : public Device
{
private:
    int rSpeed;
    bool isReverse, isRunning;
    Servo dribler;
public:
    Dribbler(int id) : Device(id) 
    {
        rSpeed = 0;
        isRunning = false;
        isReverse = false;
    }
    ~Dribbler() { }

    int updateDelay() override
    {
        return 1;  // Refresh every 20ms
    }

    void collectData() override
    { 
        // send data to dribbler
        if(isRunning)
        {
            int sp = map(rSpeed, 0, 100, 0, 110);
            dribler.writeMicroseconds(!isReverse? MID_PWM - sp : MID_PWM + sp);
        } 
        else dribler.writeMicroseconds(MID_PWM);
    }

    void connectToDevice() override
    {
        dribler.attach(DRIBBLER_PIN);
        delay(100);
        dribler.writeMicroseconds(MID_PWM);
        delay(1750);
    }

    bool isConnected() override 
    {
        return true;
    }

    void stop() 
    {
        isRunning = false;
    }

    void start()
    {
        isRunning = true;
    }

    void start(int spd)
    {
        isRunning = true;
        rSpeed = spd;
        if(spd == 0)
            isRunning = false;
    }

    void start(int spd, bool r)
    {
        isReverse = r;
        isRunning = true;
        rSpeed = spd;
        if(spd == 0)
            isRunning = false;
    }

    void start(bool r) 
    {
        isReverse = r;
        isRunning = true;
    }

    void setSpeed(int spd)
    {
        rSpeed = spd;
        if(spd == 0)
            isRunning = false;
    }

    void setReverse(bool r)
    {
        isReverse = r;
    }
    
};