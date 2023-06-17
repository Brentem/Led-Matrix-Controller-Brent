#pragma once

#include <SimpleRowDrawer.hpp>

// #define BUFFER_COUNT 16
#define BUFFER_COUNT 8
#define ROW_LENGTH 32

#define LATCH 0
#define OUTPUT_ENABLE 1
#define STOP_SIGNALS 2

class SimpleMatrixDrawer
{
    private:
        SimpleRowDrawer& rowDrawer;
        MatrixTimer& timer;
        MatrixPinLayout layout;

        // uint32_t redBuffer[BUFFER_COUNT];
        // uint32_t greenBuffer[BUFFER_COUNT];
        // uint32_t blueBuffer[BUFFER_COUNT];
        uint8_t colorBuffer[BUFFER_COUNT][ROW_LENGTH];

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