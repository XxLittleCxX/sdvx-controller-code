#include <Encoder.h>
#include "HID-Project.h"

Encoder knobLeft(0, 1);
Encoder knobRight(2,3);
#define VOL_L_SENSE 0.25
#define VOL_R_SENSE 0.25
// BT ABCD FX LR START
uint8_t buttonPins[] = {5,6,7,8,9,10,11};
uint8_t buttonLights[] = {A0,A1,A2,A3,A4,A5,13};
char buttonKeys[] = {'d','f','j','k','c','m',' '};
uint8_t buttonPressed[] = {false,false,false,false,false,false,false};

void setup() {
  Mouse.begin();
  Keyboard.begin();
  for(auto pin: buttonPins){
    pinMode(pin, INPUT_PULLUP);
  }
  for(auto pin: buttonLights){
    pinMode(pin, OUTPUT);
  }
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

  for(int i=0;i<7;i++){
    if(buttonPressed[i]){
      digitalWrite(buttonLights[i], 1);
    }else{
      digitalWrite(buttonLights[i], 0);
    }
    auto read = digitalRead(buttonPins[i]);
    Serial.println(read);
    if(read == LOW && !buttonPressed[i]){
      Keyboard.press(buttonKeys[i]);
      buttonPressed[i] = true;
    }else if(read == HIGH && buttonPressed[i]){
      Keyboard.release(buttonKeys[i]);
      buttonPressed[i] = false;
    }
  }
}