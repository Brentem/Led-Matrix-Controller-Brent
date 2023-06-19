#include "Matrix.hpp"

extern "C"
{
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include "my_gpio.h"
}

static volatile bool _clkEnable = false;
static volatile bool _clkActive = false;
static volatile bool _clkSemaphore = false;
static volatile uint8_t _latchVal = LATCH_LOAD;
static volatile uint8_t _counter = 0;

static uint8_t colours[ADDRESS_COUNT]  = {RED, GREEN, BLUE, CYAN,
                                        MAGENTA, YELLOW, WHITE, BLACK};

ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
    if(_clkEnable)
    {
        ToggleClock();
        _clkActive = !_clkActive;
        _clkSemaphore = true;
    }
    else
    {
        SetLatchPins(_latchVal);
        _latchVal >>= 1;
        _latchVal &= LATCH_MASK;
        _counter++;
    }
}

Matrix::Matrix()
{
    for(int j = 0; j < ADDRESS_COUNT; j++)
    {
        for(int i = 0; i < ROW_LENGTH; i++)
        {
            colorBuffer[j][i] = colours[j];
        }
    }

    column = 0;
    address = 0;
    addressSet = false;
    dataLoaded = false;
    columnMax = false;
}

void Matrix::Setup()
{
    GPIO_Setup();

    // Activate Interrupt
    TCCR0A = 0;
    TCCR0A &= ~(1 << WGM00);
    TCCR0A |= (1 << WGM01);

    TCCR0B &= ~(1 << CS02);
    TCCR0B |= (1 << CS01);
    TCCR0B &= ~(1 << CS00);

    TCNT0 = 0;
    OCR0A = 80;

    TIMSK0 = (1 << OCIE0A);

    sei();

    // End of Interrupt activation code
    _clkEnable = true;
}

void Matrix::Update()
{
    if(address > 7)
    {
        address = 0;
    }

    if(!addressSet)
    {
        addressSet = true;
        SetAddressPins(address);
    }

    if(!dataLoaded)
    {
        SetColorPins(colorBuffer[address][column]);
        column++;
        dataLoaded = true;
    }

    if(_clkSemaphore)
    {
        _clkSemaphore = false;
        dataLoaded = _clkActive;

        if(columnMax && !_clkActive)
        {
            column = 0;
            SetColorPins(0);
            address++;
            _clkEnable = false;
        }
    }

    columnMax = (column == ROW_LENGTH);

    if(_counter == 3)
    {
        _counter = 0;
        _latchVal = LATCH_LOAD;
        _clkEnable = true;
        addressSet = false;
    }
}