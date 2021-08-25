#pragma once

#include "Device.h"
#include "../Defines.h"

#include "Gyro.h"
#include "BallSensor.h"
#include "LineSensor.h"
#include "Dribbler.h"
#include "Kicker.h"
#include "Cam.h"
#include "../Utils/Log.h"

class DevicesController
{
private:
    Device *devices[ DEVICES_COUNT ];
public:
    DevicesController()
    {
        for(int i = 0; i < DEVICES_COUNT; ++i)
            devices[i] = nullptr;

        // Createing all devices
        Log::nl();
        Log::success("Device controller created");
        Log::info("     Creating devices...");
        devices[ GYRO_DEVICE_ID ] = new Gyro( GYRO_DEVICE_ID );
        devices[ BALL_DEVICE_ID ] = new BallSensor( BALL_DEVICE_ID );
        devices[ LINE_DEVICE_ID ] = new LineSensor( LINE_DEVICE_ID );
        devices[ KICK_DEVICE_ID ] = new Kicker( KICK_DEVICE_ID );
        devices[ DRIB_DEVICE_ID ] = new Dribbler( DRIB_DEVICE_ID );
        devices[ CAM_DEVICE_ID ] = new Cam( CAM_DEVICE_ID );

        for(int i = 0; i < DEVICES_COUNT; ++i)
            devices[i]->connect();
    }

    ~DevicesController()
    {
        for(int i = 0; i < DEVICES_COUNT; ++i)
            delete devices[i];
    }

    void update()
    {
        for(int i = 0; i < DEVICES_COUNT; ++i){
            if(devices[i] != nullptr)
                devices[i]->update();
            else Log::error("Devices controller: Device with ID " + String(i) + " is NULL!");
        }
    }

    template <typename DeviceClass>
    DeviceClass getDevice(int deviceId)
    {
        return (DeviceClass) devices[deviceId];
    }
};