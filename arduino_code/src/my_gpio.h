#ifndef MY_GPIO_H
#define MY_GPIO_H

#include <avr/io.h>
#include <stdint.h>

#define COLOR_MASK 0xFC
#define ADDRESS_MASK 0x07
#define LATCH_MASK 0x06

#define PORTB_MASK 0x07

void GPIO_Setup();

inline void SetColorPins(uint8_t val)
{
    PORTD &= ~COLOR_MASK;
    PORTD |= val << 2;
}

inline void SetAddressPins(uint8_t val)
{
    PORTC &= ~ADDRESS_MASK;
    PORTC |= val;
}

inline void ToggleClock()
{
    PORTB ^= 1;
}

inline void SetLatchPins(uint8_t val)
{
    PORTB &= ~LATCH_MASK;
    PORTB |= val;
}

#endif