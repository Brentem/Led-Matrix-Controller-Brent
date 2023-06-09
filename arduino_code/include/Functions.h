#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>

typedef struct
{
    void(*pinModePtr)(uint8_t, uint8_t);
    void(*digitalWritePtr)(uint8_t, uint8_t);
    void(*setColorPins)(uint8_t);
}IOFunction;


#endif