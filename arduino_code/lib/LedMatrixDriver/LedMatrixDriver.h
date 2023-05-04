#ifndef LED_MATRIX_DRIVER_H
#define LED_MATRIX_DRIVER_H

#define CLOCK_TIME_IN_MICRO 1

#include <stdint.h>

struct PinLayout
{
    uint8_t clk;
    uint8_t oe;
    uint8_t lat;
    uint8_t addrA;
    uint8_t addrB;
    uint8_t addrC;
    uint8_t r1, g1, b1;
    uint8_t r2, g2, b2;
};

class LedMatrixDriver
{
    private:
        PinLayout _layout;
        void(*_pinModePtr)(uint8_t, uint8_t);
        void(*_digitalWritePtr)(uint8_t, uint8_t);
        uint32_t _blueBuffer[16];
        int64_t _time;
        bool _clkSignal;
        bool _start;
        uint8_t _row;
        uint8_t _column;

        void setPinMode();
        void setDigitalWrite();

    public:
        LedMatrixDriver(PinLayout layout, 
                        void(*pinModePtr)(uint8_t, uint8_t),
                        void(*digitalWritePtr)(uint8_t, uint8_t));
        void Setup();
        void WriteBuffer(uint8_t x, uint8_t y, uint8_t val);
        void Loop();
};

#endif