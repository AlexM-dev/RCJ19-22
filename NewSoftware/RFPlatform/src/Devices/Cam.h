#pragma once

#include "Device.h"
#include "../Defines.h"
#include "../Utils/Log.h"

class Cam : public Device
{
private:
    int blueAngle, blueDistance;
    int yellowAngle, yellowDistance;
    int data[4] = {0};

public:
    Cam(int id) : Device(id) { }
    ~Cam() { }

    int updateDelay() override
    {
        return 5;  // Refresh every 20ms
    }

    void collectData() override
    { 
        if(Serial2.available() >= 13)
        {
            char v = Serial2.read();
            if(v == '*')
            {
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

            yellowAngle = data[0];
            yellowDistance = data[1];
            blueAngle = data[2];
            blueDistance = data[3];
            //Log::info(yellowAngle);
        }
    }

    void connectToDevice() override
    {
        Serial2.begin(115200);
    }

    bool isConnected() override 
    {
        return Serial2;
    }

    int getMyAngle()
    {
        return GOALS == 1? blueAngle : yellowAngle;    
    }
    int getMyDist()
    {
        return GOALS == 1? 
            abs(blueDistance * cos(radians(blueAngle)))    :
            abs(yellowDistance * cos(radians(yellowAngle)));    
    }
    int getRivalAngle()
    {
        return GOALS == 1? yellowAngle : blueAngle;    
    }
    int getRivalDist()
    {
        return GOALS == 1? 
            abs(yellowDistance * cos(radians(yellowAngle))) :
            abs(blueDistance * cos(radians(blueAngle)))     ; 
    }
};
