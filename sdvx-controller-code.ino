#include <Encoder.h>
#include "HID-Project.h"

Encoder knobLeft(0, 1);
Encoder knobRight(2,3);
#define VOL_L_SENSE 0.25
#define VOL_R_SENSE 0.25

void setup() {
  Mouse.begin();
}

long positionLeft  = -999;
long positionRight = -999;

void loop() {
  delay(2);
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  Mouse.move((positionLeft - newLeft) * VOL_L_SENSE, (newRight - positionRight) * VOL_R_SENSE);
  positionLeft = newLeft;
  positionRight = newRight;
}