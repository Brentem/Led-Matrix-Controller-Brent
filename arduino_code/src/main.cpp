#include <Arduino.h>

#include <LedMatrixDriver.h>

#define BAUDRATE 9600

#define CLK  8
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

PinLayout pinLayout
{
  .clk = CLK,
  .oe = OE,
  .lat = LAT,
  .addrA = A,
  .addrB = B,
  .addrC = C,
  .r1 = 2,
  .g1 = 3,
  .b1 = 4,
  .r2 = 5,
  .g2 = 6,
  .b2 = 7
};

LedMatrixDriver driver(pinLayout, pinMode, digitalWrite);

void setup() {
  // put your setup code here, to run once:
  driver.Setup();

  for(uint8_t y = 0; y < 1; y++)
  {
    for(uint8_t x = 0; x < 32; x++)
    {
      driver.WriteBuffer(x, y, 1);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  driver.Loop();
}