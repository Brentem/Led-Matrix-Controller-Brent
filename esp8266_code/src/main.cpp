#include <Arduino.h>

#include "Led.hpp"
#include "../custom_libs/SerialHandler/SerialHandler.hpp"

#define BAUDRATE 9600
#define LED_PIN D1
#define BUTTON_1_PIN D5
#define BUTTON_2_PIN D6
#define SECOND 1000

SerialHandler serialHandler(BAUDRATE);
Led led(LED_PIN, SECOND);

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_1_PIN, INPUT);
  pinMode(BUTTON_2_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  serialHandler.BuildMessage();
  led.Update();

  if(serialHandler.MessageRetreived())
  {
    char* msg = serialHandler.GetRetreivedMessage();

    if(strcmp(msg, "ACK") == 0)
    {
      led.On();
    }
  }

  if(digitalRead(BUTTON_1_PIN) == HIGH)
  {
    serialHandler.SendMessage("Option1");
  }

  if(digitalRead(BUTTON_2_PIN) == HIGH)
  {
    serialHandler.SendMessage("Option2");
  }
}