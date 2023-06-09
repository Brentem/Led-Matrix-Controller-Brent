#pragma once

#include <SimpleRowDrawer.hpp>

#define BUFFER_COUNT 16

#define LATCH 1
#define OUTPUT_ENABLE 2
#define STOP_SIGNALS 3

class SimpleMatrixDrawer
{
    private:
        SimpleRowDrawer& rowDrawer;
        MatrixTimer& timer;
        MatrixPinLayout layout;

        uint32_t redBuffer[BUFFER_COUNT];
        uint32_t greenBuffer[BUFFER_COUNT];
        uint32_t blueBuffer[BUFFER_COUNT];

        bool drawEnable;
        bool signalEnable;
        uint8_t signalCounter;

        uint8_t address;
        bool addressSet;

        void(*pinMode)(uint8_t, uint8_t);
        void(*digitalWrite)(uint8_t, uint8_t);

        void setAddress();
        void handleTimer();
        void setOE_Latch();

    public:
        SimpleMatrixDrawer(SimpleRowDrawer& rowDrawer, MatrixTimer& timer,
         MatrixPinLayout layout, IOFunction function);
        void Setup();
        void TempFunction();
        void Draw();
};