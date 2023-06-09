#pragma once

#include <stdint.h>

#include "../../include/PinLayout.h"
#include "../../include/Functions.h"

#include <MatrixTimer.hpp>

#define ROW_COUNT_PER_COLOR 2

class SimpleRowDrawer
{
    private:
        MatrixTimer& timer;
        uint32_t redRows[ROW_COUNT_PER_COLOR];
        uint32_t greenRows[ROW_COUNT_PER_COLOR];
        uint32_t blueRows[ROW_COUNT_PER_COLOR];
        RowPinLayout layout;
        void(*pinMode)(uint8_t, uint8_t);
        void(*digitalWrite)(uint8_t, uint8_t);
        void(*setColorPins)(uint8_t);
        bool clockActive;
        bool dataLoaded;
        uint8_t column;

        void loadData();
        void drawPixel(uint8_t pin, uint32_t row);
        void drawPixels();
        void toggleClock();
    public:
        SimpleRowDrawer(MatrixTimer& timer, RowPinLayout layout, IOFunction function);
        void Setup();
        void SetRows(uint32_t* redArray, uint32_t* greenArray, uint32_t* blueArray);
        bool Draw(bool drawEnable);
};