#pragma once

#include <stdint.h>

class Timer
{
private:
    uint64_t startTime;
    uint32_t delayInMs;
    bool started;
    bool finished;

public:
    Timer();
    void Start(uint32_t delayInMs);
    void Run();
    void Reset();
    bool Finished() const;
};