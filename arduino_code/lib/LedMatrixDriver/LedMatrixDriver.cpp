#include <LedMatrixDriver.h>

#include <Arduino.h> // Only for micros

const uint8_t outputMode = 1;

const uint8_t low = 0;
const uint8_t high = 1;

const uint8_t rowLength = 32;

LedMatrixDriver::LedMatrixDriver(PinLayout layout,
                                 void (*pinModePtr)(uint8_t, uint8_t),
                                 void (*digitalWritePtr)(uint8_t, uint8_t))
{
    layout = layout;
    pinModePtr = pinModePtr;
    digitalWritePtr = digitalWritePtr;
    start = true;
    clkSignal = false;
    dataLoaded = false;
    row = 0;
    column = 0;
}

void LedMatrixDriver::Setup()
{
    setPinMode();
    setDigitalWrite();
}

void LedMatrixDriver::WriteBuffer(uint8_t x, uint8_t y, uint8_t val)
{
    uint32_t row = blueBuffer[y];
    uint32_t valMask = val << ((rowLength - 1) - x);

    if (val > 0)
    {
        row = row | valMask;
    }
    else
    {
        row = row & ~valMask;
    }

    blueBuffer[y] = row;
}

void LedMatrixDriver::Loop()
{
    if (start)
    {
        time = micros();
        start = false;
    }

    int64_t currentTime = micros();

    if ((currentTime - time) >= CLOCK_TIME_IN_MICRO)
    {
        clkSignal = !clkSignal;
        time = micros();
    }

    if (clkSignal)
    {
        digitalWritePtr(layout.clk, high);
    }
    else
    {
        digitalWritePtr(layout.clk, low);

        if (!dataLoaded)
        {
            uint32_t data = blueBuffer[row] & (1 << ((rowLength - 1) - column));
            data = ((rowLength - 1) - column) >> data;
            digitalWritePtr(layout.b1, (uint8_t)data);
            column++;
        }
    }

    if (column == rowLength)
    {
        column = 0;
        row++;
    }
}

void LedMatrixDriver::setPinMode()
{
    pinModePtr(layout.clk, outputMode);
    pinModePtr(layout.oe, outputMode);
    pinModePtr(layout.lat, outputMode);
    pinModePtr(layout.addrA, outputMode);
    pinModePtr(layout.addrB, outputMode);
    pinModePtr(layout.addrC, outputMode);
    pinModePtr(layout.r1, outputMode);
    pinModePtr(layout.g1, outputMode);
    pinModePtr(layout.b1, outputMode);
    pinModePtr(layout.r2, outputMode);
    pinModePtr(layout.g2, outputMode);
    pinModePtr(layout.b2, outputMode);
}

void LedMatrixDriver::setDigitalWrite()
{
    digitalWritePtr(layout.clk, low);
    digitalWritePtr(layout.oe, low);
    digitalWritePtr(layout.lat, low);
    digitalWritePtr(layout.addrA, low);
    digitalWritePtr(layout.addrB, low);
    digitalWritePtr(layout.addrC, low);
    digitalWritePtr(layout.r1, low);
    digitalWritePtr(layout.g1, low);
    digitalWritePtr(layout.b1, low);
    digitalWritePtr(layout.r2, low);
    digitalWritePtr(layout.g2, low);
    digitalWritePtr(layout.b2, low);
}