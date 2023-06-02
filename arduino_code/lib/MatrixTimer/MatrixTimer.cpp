#include <MatrixTimer.hpp>

MatrixTimer::MatrixTimer(unsigned long(*time)())
{
    this->time = time;
    prevTime = 0;
    cycleTime = 0;
    started = false;
    finished = false;
}

void MatrixTimer::Start(uint32_t cycleTime)
{
    finished = false;
    started = true;
    this->cycleTime = cycleTime;
    prevTime = time();
}

void MatrixTimer::Run()
{
    if(!started)
    {
        return;
    }

    uint64_t currentTime = time();

    if((currentTime - prevTime) >= cycleTime)
    {
        started = false;
        finished = true;
    }
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