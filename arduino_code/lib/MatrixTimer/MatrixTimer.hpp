#pragma once

#include <stdint.h>

class MatrixTimer
{
    private:
        unsigned long(*time)();
        uint64_t prevTime;
        uint64_t currentTime;
        uint32_t cycleTime;
        bool started;
        bool finished;
        bool temp;
    public:
        MatrixTimer(unsigned long(*time)());
        void Start(uint32_t cycleTime);
        void Run();
        void Stop();
        bool IsStarted() const;
        bool IsFinished() const;
        void Reset();
        void SetTemp();
};