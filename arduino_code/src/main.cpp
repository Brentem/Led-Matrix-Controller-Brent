#include <Arduino.h>

#include <SimpleMatrixDrawer.hpp>

extern "C"
{
  #include "my_gpio.h"
}

#define BAUDRATE 9600

#define CLK  8
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

IOFunction function
{
  .pinModePtr = pinMode,
  .digitalWritePtr = myDigitalWrite,
  .setColorPins = SetColorPins
};

RowPinLayout rowLayout
{
  .clk = CLK,
  .r1 = 2,
  .g1 = 3,
  .b1 = 4,
  .r2 = 5,
  .g2 = 6,
  .b2 = 7
};

MatrixPinLayout matrixLayout
{
  .oe = OE,
  .lat = LAT,
  .addrA = A,
  .addrB = B,
  .addrC = C
};

ISR(TIMER0_COMPA_vect)
{
  PORTB ^= 1;
}

// MatrixTimer rowTimer(micros);
// SimpleRowDrawer rowDrawer(rowTimer, rowLayout, function);

// MatrixTimer matrixTimer(micros);
// SimpleMatrixDrawer matrixDrawer(rowDrawer, matrixTimer, matrixLayout, function);

void setup() {
  // put your setup code here, to run once:
  pinMode(CLK, OUTPUT);
  // matrixDrawer.Setup();
  // matrixDrawer.TempFunction();

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
}

void loop() {
  // put your main code here, to run repeatedly:
  // matrixDrawer.Draw();
}