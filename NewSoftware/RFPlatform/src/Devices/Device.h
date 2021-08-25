#pragma once

#include <Arduino.h>
#include "../Utils/Log.h"

#define DEVICE_CONNTECTION_ATTEMPTS 2
#define DEVICE_CONNTECTION_DELAY 350

#define DEVICE_RECONNTECTION_ATTEMPTS 5
#define DEVICE_RECONNTECTION_DELAY 250

class Device
{
private:
    long long prevDeviceUpdateMillis;
    int updateTime;
    int attempts;

    int deviceID;

public:
    Device(int id)
    {   
        deviceID = id;
        prevDeviceUpdateMillis = 0; 
    }

    ~Device()
    {
    }

    void connect()
    {
        attempts = 1;

        Log::nl();
        Log::info("Connecting to device[" + String(deviceID) + "]");

        connectToDevice();
        while (!isConnected()){
            Log::warning("     Connecting to device. Attempt " + String(attempts));
            delay(DEVICE_CONNTECTION_DELAY);
            connectToDevice();
            attempts++;
            if(attempts > DEVICE_CONNTECTION_ATTEMPTS)
                break;
        }

        if(isConnected())
            Log::success("     Device connected");
        else 
            Log::error("     Cant connect to this device!");

        attempts = 1;
        updateTime = updateDelay();
    }

    void reconnect()
    {
        if(attempts == DEVICE_RECONNTECTION_ATTEMPTS + 1) {
            Log::error("Device[" + String(deviceID) + "] Reconnection failed! Device OFFLINE!");
            attempts++;
            return;
        }
        if(attempts > DEVICE_RECONNTECTION_ATTEMPTS + 1)
            return;
        connectToDevice();
        Log::warning("Device[" + String(deviceID) + "] is disconnected. Reconnecting, attempt " + String(attempts));
        attempts++;
        updateTime = DEVICE_RECONNTECTION_DELAY;
    }

    void reconnected()
    {
        if(attempts <= 1)
            return;
        Log::success("Device[" + String(deviceID) + "] Reconnection success! Device ONLINE!");
        attempts = 1;
        updateTime = updateDelay();
    }

    void update()
    {
        if(millis() - prevDeviceUpdateMillis >= updateTime)
        {
            if(isConnected())
            {
                reconnected();
                collectData();
            }
            else reconnect();
                
            prevDeviceUpdateMillis = millis();
        }
    }

    virtual int updateDelay() { return 50; };     // Get Device Update Rate
    virtual void collectData() { };               // Update Device Data
    virtual void connectToDevice() { };           // Connect to device
    virtual bool isConnected() { return false; }; // Return connection status
};