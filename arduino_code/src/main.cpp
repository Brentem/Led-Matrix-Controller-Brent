#include <Arduino.h>

#include <RGBmatrixPanel.h>

#include <SerialHandler.hpp>

#define BAUDRATE 9600

#define CLK  8
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
SerialHandler serialHandler(BAUDRATE);

void DrawBlue()
{
  for(uint8_t x=0; x<4; x++) 
  {
    for(uint8_t y=0; y<4; y++) 
    {
      matrix.drawPixel(x, y, matrix.Color333(0, 0, 3));
    }
  }
}

void DrawRed()
{
  for(uint8_t x=0; x<4; x++) 
  {
    for(uint8_t y=0; y<4; y++) 
    {
      matrix.drawPixel(x, y, matrix.Color333(3, 0, 0));
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  serialHandler.Begin();
  matrix.begin();
  DrawBlue();
}

void loop() {
  // put your main code here, to run repeatedly:

  serialHandler.BuildMessage();

  if(serialHandler.MessageRetreived())
  {
    char* msg = serialHandler.GetRetreivedMessage();

    if(strcmp(msg, "Option1") == 0)
    {
      DrawBlue();
      serialHandler.SendMessage("ACK");
      serialHandler.Clear();
    }

    if(strcmp(msg, "Option2") == 0)
    {
      DrawRed();
      serialHandler.SendMessage("ACK");
      serialHandler.Clear();
    }
  }
}