#pragma once

#include <stdint.h>

class MatrixTimer
{
    private:
        unsigned long(*time)();
        uint64_t prevTime;
        uint32_t cycleTime;
        bool started;
        bool finished;
    public:
        MatrixTimer(unsigned long(*time)());
        void Start(uint32_t cycleTime);
        void Run();
        bool IsStarted() const;
        bool IsFinished() const;
        void Reset();
};