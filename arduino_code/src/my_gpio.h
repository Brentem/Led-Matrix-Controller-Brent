#ifndef MY_GPIO_H
#define MY_GPIO_H

#include <stdint.h>

#define FILTER_MASK 0x01

#define BIT_MASK_0 0x01
#define BIT_MASK_1 0x02
#define BIT_MASK_2 0x04
#define BIT_MASK_3 0x08
#define BIT_MASK_4 0x10
#define BIT_MASK_5 0x20
#define BIT_MASK_6 0x40
#define BIT_MASK_7 0x80
#define BIT_COUNT 8

#define PORTB_MIN 8 //PB0
#define PORTB_MAX 13 //PB5

#define PORTC_MIN 14 //PC0
#define PORTC_MAX 19 //PC5

#define PORTD_MIN 0 //PD0
#define PORTD_MAX 7 //PD7

#define COLOR_MASK 0xFC

void myDigitalWrite(uint8_t pin, uint8_t val);
void SetColorPins(uint8_t val);

#endif