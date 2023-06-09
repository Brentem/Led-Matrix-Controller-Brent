#ifndef PINLAYOUT_H
#define PINLAYOUT_H

#include <stdint.h>

typedef struct
{
    uint8_t oe;
    uint8_t lat;
    uint8_t addrA;
    uint8_t addrB;
    uint8_t addrC;
}MatrixPinLayout;

typedef struct
{
    uint8_t clk;
    uint8_t r1, g1, b1;
    uint8_t r2, g2, b2;
}RowPinLayout;


#endif