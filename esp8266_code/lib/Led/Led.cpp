#include "Led.hpp"

#include <Arduino.h>

Led::Led(int pinNumber, uint32_t ledOnTime)
{
    this->ledOnTime = ledOnTime;
    this->pinNumber = pinNumber;

    timer.Reset();
    pinMode(pinNumber, OUTPUT);
}

void Led::On()
{
    digitalWrite(pinNumber, HIGH);

    timer.Start(ledOnTime);
}

void Led::Update()
{
    timer.Run();

    if(timer.Finished())
    {
        digitalWrite(pinNumber, LOW);
    }
}

void Led::Off()
{
    digitalWrite(pinNumber, LOW);
    timer.Reset();
}