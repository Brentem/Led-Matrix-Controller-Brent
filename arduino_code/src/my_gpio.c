#include "my_gpio.h"

#include <avr/io.h>

// static uint8_t bitMaskArray[BIT_COUNT] =
// {
//     BIT_MASK_0,
//     BIT_MASK_1,
//     BIT_MASK_2,
//     BIT_MASK_3,
//     BIT_MASK_4,
//     BIT_MASK_5,
//     BIT_MASK_6,
//     BIT_MASK_7
// };

// void myDigitalWrite(uint8_t pin, uint8_t val)
// {
//     uint8_t filteredVal = FILTER_MASK & val;

//     if((pin >= PORTB_MIN) && (pin <= PORTB_MAX))
//     {
//         uint8_t offset = pin - PORTB_MIN;
//         uint8_t bitMask = bitMaskArray[offset];
//         PORTB &= ~bitMask;
//         PORTB |= filteredVal << offset;
//     }
//     else if((pin >= PORTC_MIN) && (pin <= PORTC_MAX))
//     {
//         uint8_t offset = pin - PORTC_MIN;
//         uint8_t bitMask = bitMaskArray[offset];
//         PORTC &= ~bitMask;
//         PORTC |= filteredVal << offset;
//     }
//     else if((pin >= PORTD_MIN) && (pin <= PORTD_MAX))
//     {
//         uint8_t bitMask = bitMaskArray[pin];
//         PORTD &= ~bitMask;
//         PORTD |= filteredVal << pin;
//     }
// }

void inline GPIO_Setup()
{
    DDRB |= PORTB_MASK;
    DDRC |= ADDRESS_MASK;
    DDRD |= COLOR_MASK;
}

void inline SetColorPins(uint8_t val)
{
    PORTD &= ~COLOR_MASK;
    PORTD |= val << 2;
}

void inline SetAddressPins(uint8_t val)
{
    PORTC &= ADDRESS_MASK;
    PORTC |= val;
}

void inline ToggleClock()
{
    PORTB ^= 1;
}

void inline SetLatchPins(uint8_t val)
{
    PORTB &= LATCH_MASK;
    PORTB |= val;
}