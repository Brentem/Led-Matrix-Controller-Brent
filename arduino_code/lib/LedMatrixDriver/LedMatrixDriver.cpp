#include <LedMatrixDriver.h>

#include <Arduino.h> // Only for micros

const uint8_t outputMode = 1;

const uint8_t low = 0;
const uint8_t high = 1;

LedMatrixDriver::LedMatrixDriver(PinLayout layout,
                                void(*pinModePtr)(uint8_t, uint8_t),
                                void(*digitalWritePtr)(uint8_t, uint8_t))
{
    _layout = layout;
    _pinModePtr = pinModePtr;
    _digitalWritePtr = digitalWritePtr;
    _start = true;
    _clkSignal = false;
    _row = 0;
    _column = 0;
}

void LedMatrixDriver::Setup()
{
    setPinMode();
    setDigitalWrite();
}

void LedMatrixDriver::WriteBuffer(uint8_t x, uint8_t y, uint8_t val)
{
    uint32_t row = _blueBuffer[y];
    uint32_t valMask = val << (31 - x);

    if(val > 0)
    {
        row = row | valMask;
    }
    else
    {
        row = row & ~valMask;
    }

    _blueBuffer[y] = row;
}

void LedMatrixDriver::Loop()
{
    if(_start)
    {
        _time = micros();
        _start = false;
    }

    int64_t currentTime = micros();

    if((currentTime - _time) >= CLOCK_TIME_IN_MICRO)
    {
        _clkSignal = !_clkSignal;
        _time = micros();
    }

    if(_clkSignal)
    {
        _digitalWritePtr(_layout.clk, high);
    }
    else
    {
        _digitalWritePtr(_layout.clk, low);
    }


}

void LedMatrixDriver::setPinMode()
{
    _pinModePtr(_layout.clk, outputMode);
    _pinModePtr(_layout.oe, outputMode);
    _pinModePtr(_layout.lat, outputMode);
    _pinModePtr(_layout.addrA, outputMode);
    _pinModePtr(_layout.addrB, outputMode);
    _pinModePtr(_layout.addrC, outputMode);
    _pinModePtr(_layout.r1, outputMode);
    _pinModePtr(_layout.g1, outputMode);
    _pinModePtr(_layout.b1, outputMode);
    _pinModePtr(_layout.r2, outputMode);
    _pinModePtr(_layout.g2, outputMode);
    _pinModePtr(_layout.b2, outputMode);
}

void LedMatrixDriver::setDigitalWrite()
{
    _digitalWritePtr(_layout.clk, low);
    _digitalWritePtr(_layout.oe, low);
    _digitalWritePtr(_layout.lat, low);
    _digitalWritePtr(_layout.addrA, low);
    _digitalWritePtr(_layout.addrB, low);
    _digitalWritePtr(_layout.addrC, low);
    _digitalWritePtr(_layout.r1, low);
    _digitalWritePtr(_layout.g1, low);
    _digitalWritePtr(_layout.b1, low);
    _digitalWritePtr(_layout.r2, low);
    _digitalWritePtr(_layout.g2, low);
    _digitalWritePtr(_layout.b2, low);
}