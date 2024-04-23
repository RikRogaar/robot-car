#include "MotorController.h"

MotorController::MotorController(int cwPin, int ccwPin) {
  pinCW = cwPin;
  pinCCW = ccwPin;
  pinMode(pinCW, OUTPUT);
  pinMode(pinCCW, OUTPUT);
  stop();
}

void MotorController::forward() {
  analogWrite(pinCW, 255);
  analogWrite(pinCCW, 0);
}

void MotorController::backward() {
  analogWrite(pinCW, 0);
  analogWrite(pinCCW, 255);
}

void MotorController::stop() {
  analogWrite(pinCW, 0);
  analogWrite(pinCCW, 0);
}