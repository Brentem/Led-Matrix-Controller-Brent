#pragma once

#include <stdint.h>

class Timer
{
private:
    int64_t startTime;
    int32_t delayInMs;
    bool started;
    bool finished;

public:
    Timer();
    void Start(int32_t delayInMs);
    void Run();
    void Reset();
    bool Finished() const;
};