#include <MatrixTimer.hpp>

MatrixTimer::MatrixTimer(unsigned long(*time)())
{
    this->time = time;
    prevTime = 0;
    currentTime = 0;
    cycleTime = 0;
    started = false;
    finished = false;
    temp = true;
}

void MatrixTimer::Start(uint32_t cycleTime)
{
    finished = false;
    started = true;
    this->cycleTime = cycleTime;
    // prevTime = time();

    if(temp)
    {
        currentTime = time();
        prevTime = currentTime;
    }
}

void MatrixTimer::Run()
{
    if(!started)
    {
        return;
    }

    if(temp)
    {
        temp = false;
    }
    else
    {
        currentTime = time();
    }

    if((currentTime - prevTime) >= cycleTime)
    {
        started = false;
        finished = true;
        prevTime = currentTime;
    }
}

void MatrixTimer::Stop()
{
    started = false;
    finished = false;
}

bool MatrixTimer::IsStarted() const
{
    return started;
}

bool MatrixTimer::IsFinished() const
{
    return finished;
}

void MatrixTimer::Reset()
{
    prevTime = 0;
    cycleTime = 0;
    started = false;
    finished = false; 
}

void MatrixTimer::SetTemp()
{
    temp = true;
}