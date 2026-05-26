#include <Servo.h>

Servo esc;
int encoderPinA = 2;
int encoderPinB = 3;
volatile int encoderPos = 0;

void setup() {
  esc.attach(9);              // ESC signal wire
  esc.writeMicroseconds(1000); // Arm ESC
  delay(2000);

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
}

void loop() {
  // Map encoder position to throttle range
  int throttle = map(encoderPos, 0, 100, 1000, 2000);
  esc.writeMicroseconds(throttle);
}

void updateEncoder() {
  int a = digitalRead(encoderPinA);
  int b = digitalRead(encoderPinB);
  if (a == b) encoderPos++;
  else encoderPos--;
}

