#pragma once

class Timer;
class ITimer
{
public:
    virtual void OnTimerEnd(Timer *timer) = 0;
};