#pragma once

#include "../Interfaces/ITimer.h"

enum TimerState 
{
    WAITING,
    RUNNING,
    STOPPED
};

class Timer
{
private:
    int id, delay;
    bool running, loop;
    unsigned long long prev;
    ITimer *interface;
    TimerState state;

    void onTimerEnd()
    {
        if(interface != nullptr)
            interface->OnTimerEnd(this);
        if(loop)
            start();
        else
            stop();
    }
public:
    Timer(int id, int delay, ITimer *interface, bool loop = false)
    {
        this->id = id;
        this->delay = delay;
        running = false;
        this->loop = loop;
        this->interface = interface;
        state = WAITING;
    }

    void update()
    {
        if(millis() - prev >= delay && running)
            onTimerEnd();
    }

    void start()
    {
        running = true;
        prev = millis();
        state = RUNNING;
    }

    void stop()
    {
        running = false;
        state = STOPPED;
    }

    int getID()
    {
        return id;
    }

    TimerState getState()
    {
        return state;
    }

    int getDelay()
    {
        return delay;
    }
};