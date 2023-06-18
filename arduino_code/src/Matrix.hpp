#pragma once

#include <stdint.h>

#define ADDRESS_COUNT 8
#define ROW_LENGTH 32

#define RED 0x09
#define GREEN 0x12
#define BLUE 0x24
#define CYAN 0x1B
#define MAGENTA 0x2D
#define YELLOW 0x36
#define WHITE 0x3F
#define BLACK 0x00

#define LATCH_LOAD 0x04;
#define LATCH_MASK 0x01;

class Matrix
{
    private:
        uint8_t colorBuffer[ADDRESS_COUNT][ROW_LENGTH];
        uint8_t column;
        uint8_t address;
        bool addressSet;
        bool dataLoaded;
    public:
        Matrix();
        void Setup();
        void Update();
};