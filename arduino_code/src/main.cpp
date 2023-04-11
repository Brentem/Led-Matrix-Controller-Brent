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
  for(uint8_t x=0; x<32; x++) 
  {
    for(uint8_t y=0; y<16; y++) 
    {
      matrix.drawPixel(x, y, matrix.Color333(0, 0, 7));
    }
  }
}

void DrawRed()
{
  for(uint8_t x=0; x<32; x++) 
  {
    for(uint8_t y=0; y<16; y++) 
    {
      matrix.drawPixel(x, y, matrix.Color333(7, 0, 0));
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  DrawBlue();
}

void loop() {
  // put your main code here, to run repeatedly:
  serialHandler.BuildMessage();

  if(serialHandler.MessageRetreived())
  {
    char* msg = serialHandler.GetRetreivedMessage();

    Serial.println("Arduino has received Message!");

    if(strcmp(msg, "Option1"))
    {
      DrawBlue();
      serialHandler.SendMessage("ACK");
    }

    if(strcmp(msg, "Option2"))
    {
      DrawRed();
      serialHandler.SendMessage("ACK");
    }
  }
}