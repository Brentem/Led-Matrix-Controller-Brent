#include <Arduino.h>

#include <Matrix.hpp>

Matrix matrix;

void setup() {
  // put your setup code here, to run once:
  matrix.Setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  matrix.Update();
}