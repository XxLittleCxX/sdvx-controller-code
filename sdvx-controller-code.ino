#include <Encoder.h>
#include "HID-Project.h"

#define USE_GAMEPAD
Encoder knobLeft(0, 1);
Encoder knobRight(2,3);
// BT ABCD FX LR START
uint8_t buttonPins[] = {5,6,7,8,9,10,11};
uint8_t buttonLights[] = {A0,A1,A2,A3,A4,A5,13};
char buttonKeys[] = {'d','f','j','k','c','m',' '};
uint8_t buttonPressed[] = {false,false,false,false,false,false,false};

void setup() {
  #ifdef USE_GAMEPAD
Gamepad.begin();
  #else
Mouse.begin();
Keyboard.begin();
  #endif
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
  #ifdef USE_GAMEPAD
  Gamepad.xAxis(newLeft * 70);
  Gamepad.yAxis(newRight * 70);
  #else
  Mouse.move((positionLeft - newLeft) * 0.25, (newRight - positionRight) * 0.25);
  positionLeft = newLeft;
  positionRight = newRight;
  #endif

  for(int i=0;i<7;i++){
    if(buttonPressed[i]){
      digitalWrite(buttonLights[i], 1);
    }else{
      digitalWrite(buttonLights[i], 0);
    }
    auto read = digitalRead(buttonPins[i]);
    if(read == LOW && !buttonPressed[i]){
      #ifdef USE_GAMEPAD
      Gamepad.press(i+1);
      #else
      Keyboard.press(buttonKeys[i]);
      #endif
      buttonPressed[i] = true;
    }else if(read == HIGH && buttonPressed[i]){
      #ifdef USE_GAMEPAD
      Gamepad.release(i+1);
      #else
      Keyboard.release(buttonKeys[i]);
      #endif
      buttonPressed[i] = false;
    }
  }
  Gamepad.write();
}