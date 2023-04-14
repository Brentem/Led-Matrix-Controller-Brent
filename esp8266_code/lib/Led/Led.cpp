#include "Led.hpp"

#include <Arduino.h>

Led::Led(int pinNumber, uint32_t ledOnTime)
{
    this->ledOnTime = ledOnTime;
    this->pinNumber = pinNumber;
    isLedOn = false;
}

void Led::Setup()
{
    timer.Reset();
    pinMode(pinNumber, OUTPUT);
}

void Led::On()
{
    digitalWrite(pinNumber, HIGH);
    isLedOn = true;

    timer.Start(ledOnTime);
}

void Led::Update()
{
    timer.Run();

    if(timer.Finished())
    {
        digitalWrite(pinNumber, LOW);
        isLedOn = false;
    }
}

void Led::Off()
{
    digitalWrite(pinNumber, LOW);
    isLedOn = false;
    timer.Reset();
}

bool Led::IsLedOn() const
{
    return isLedOn;
}