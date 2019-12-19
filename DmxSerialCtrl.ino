// - - - - -
// DmxSerial - A hardware supported interface to DMX.
// DmxSerialSend.ino: Sample DMX application for sending 3 DMX values.
// There levels are placed into the DMX buffer with a slow fade.
// DMXSerial works in the background and constantly sends the actual values over the DMX interface.
// The actual values are also available on the built in PWM ports:
// address 1 (white) -> also available on PWM Port 9
// 
// Copyright (c) 2011-2015 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// 
// Documentation and samples are available at http://www.mathertel.de/Arduino
// The repository is on github : https://github.com/mathertel/DMXSerial
// The repository on github is made available in the Arduino Library Manager.
//
// - - - - -

#include <DMXSerial.h>

// Constants for demo program

const int LedPin =    9;  // PWM output pin for LED

int LevelSetting;

int LevelNow = 0;

void setup() {
  DMXSerial.init(DMXController);

  pinMode(LedPin,   OUTPUT); // sets the digital pin as output
} // setup


// update level acording to joystick
void loop() {
  // read signal from joystick and scale it down to 8 bit
  int joystickY = analogRead(A0);
  int joystickX = analogRead(A1);
  
  int adjust = map(joystickY, 0, 1023, -1000, 1000);
  
  LevelSetting += adjust / 500;
  LevelSetting = constrain(LevelSetting, 0, 255);
  
  // move intensity towards setting
  if (LevelSetting != LevelNow) {
    if (LevelNow < LevelSetting)  LevelNow++; 
    if (LevelNow > LevelSetting)  LevelNow--; 
    DMXSerial.write(1, LevelNow);
    analogWrite(LedPin,   LevelNow); 
  }

  delayMicroseconds(1000); // wait a little bit
} // loop
