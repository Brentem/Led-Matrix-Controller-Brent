#include <Arduino.h>

#include <SimpleMatrixDrawer.hpp>

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
  .digitalWritePtr = digitalWrite
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

MatrixTimer rowTimer(micros);
SimpleRowDrawer rowDrawer(rowTimer, rowLayout, function);

MatrixTimer matrixTimer(micros);
SimpleMatrixDrawer matrixDrawer(rowDrawer, matrixTimer, matrixLayout, function);

void setup() {
  // put your setup code here, to run once:
  matrixDrawer.Setup();
  matrixDrawer.TempFunction();
}

void loop() {
  // put your main code here, to run repeatedly:
  matrixDrawer.Draw();
}