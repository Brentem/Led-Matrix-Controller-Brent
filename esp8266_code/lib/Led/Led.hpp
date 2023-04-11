#pragma once

#include <stdint.h>

#include <Timer.hpp>

class Led
{
private:
    Timer timer;
    uint32_t ledOnTime;
    int pinNumber;

public:
    Led(int pinNumber, uint32_t ledOnTime);
    void Setup();
    void On();
    void Update();
    void Off();
};