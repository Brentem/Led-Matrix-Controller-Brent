#include "my_gpio.h"

void GPIO_Setup()
{
    DDRB |= PORTB_MASK;
    DDRC |= ADDRESS_MASK;
    DDRD |= COLOR_MASK;

    PORTB &= ~PORTB_MASK;
    PORTC &= ~ADDRESS_MASK;
    PORTD &= ~COLOR_MASK;
}

extern inline void  SetColorPins(uint8_t val);
extern inline void SetAddressPins(uint8_t val);
extern inline void ToggleClock();
extern inline void SetLatchPins(uint8_t val);