#pragma once

#include "Device.h"
#include "../Defines.h"
#include "../Utils/Log.h"

class Kicker : public Device
{
private:
    bool isKicked;
public:
    Kicker(int id) : Device(id) { }
    ~Kicker() { }

    int updateDelay() override
    {
        return 20;  // Refresh every 20ms
    }

    void collectData() override
    { 
        // send data to kicker 
        // and then set flag to false
        isKicked = false;
    }

    void connectToDevice() override
    {
        
    }

    bool isConnected() override 
    {
        return false;
    }

    void kick() 
    {
        if(isKicked)
            return;
        isKicked = true;
        // this function only set kick flag
        // kicker must be activated from collectData function
    }
    
};
