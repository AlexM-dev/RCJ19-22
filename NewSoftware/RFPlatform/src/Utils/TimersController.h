#pragma once

#include "../Defines.h"
#include "../Interfaces/ITimer.h"
#include "Timer.h"

class TimersController
{
private:
    Timer *timers[ MAX_TIMERS_COUNT ];
    ITimer *interfacae;

    void addTimer(Timer *timer)
    {
        if(timer->getID() > MAX_TIMERS_COUNT - 1)
            return;
        timers[timer->getID()] = timer;
    }
public:
    TimersController(ITimer *interfacae)
    {
        this->interfacae = interfacae;
        for(int i = 0; i < MAX_TIMERS_COUNT; ++i)
            timers[i] = nullptr;
    }

    void update()
    {
        for(int i = 0; i < MAX_TIMERS_COUNT; ++i)
            if(timers[i] != nullptr)
                timers[i]->update();
    }

    void start(int timerID)
    {
        timers[timerID]->start();
    }

    void stop(int timerID)
    {
        timers[timerID]->stop();
    }

    void createSimpleTimer(int timerID, int delay)
    {
        addTimer(new Timer(timerID, delay, interfacae ));
    }

    void createLoopTimer(int timerID, int delay)
    {
        addTimer(new Timer(timerID, delay, interfacae, true ));
    }

    TimerState getTimerState(int timerID)
    {
        return timers[timerID]->getState();
    }
};