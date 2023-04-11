#include "Timer.hpp"

#include <Arduino.h>

Timer::Timer()
{
    startTime = 0;
    delayInMs = 0;
    started = false;
    finished = false;
}

void Timer::Start(uint32_t delayInMs)
{
    finished = false;
    started = true;
    this->delayInMs = delayInMs;
    startTime = millis();
}

void Timer::Run()
{
    if(!started)
        return;
    
    uint32_t currentTime = millis();

    if((currentTime - startTime) >= delayInMs)
    {
        started = false;
        finished = true;
    }
}

void Timer::Reset()
{
    startTime = 0;
    delayInMs = 0;
    started = false;
    finished = false;
}

bool Timer::Finished() const
{
    return finished;
}