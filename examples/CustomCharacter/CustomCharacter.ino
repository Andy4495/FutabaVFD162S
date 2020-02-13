/*
  FutabaVFD162S Library - customCharacter()

 Demonstrates the use an Futaba VFD. Tested
 with model US162SD03CB 2x16  display.

 This sketch demonstrates the use of custom characters.

  The circuit:

 * Display +5v (pin 1) & GND (pin 3) connected to regulated 5v, 500ma power supply.
 * Display GND   (pin 3) also connected to Arduino ground.
 * Display Clock (pin 2) connected to Arduino/MSP pin 5.
 * Display Data  (pin 4) connected to Arduino/MSP pin 6.
 * Display Reset (pin 5) connected to Arduino/MSP pin 8.

 Created Mar 17, 2011.

 This example code is in the public domain.

 http://arduino.cc/playground/Main/FutabaUsVfd

 Slight modification Nov 2019 to include in updated library at https://github.com/Andy4495/FutabaVFD162S
*/

// Include the library code.
#include <FutabaVFD162S.h>

FutabaVFD162S vfd(5, 6, 8);

byte openHeart[8] = {
  0b00000,
  0b01010,
  0b10101,
  0b10001,
  0b01010,
  0b00100,
  0b00000,
  0b00000
};

byte filledHeart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

void setup() {
  // Set up the VFD's number of columns and rows:
  vfd.begin(16, 2);

  // Create open heart as custom character 0.
  vfd.createChar(0, openHeart);

  // Create filled heart as custom character 1.
  vfd.createChar(1, filledHeart);

  // Print description text
  vfd.setCursor(0, 0);
  vfd.print("Custom heartbeat");
  vfd.setCursor(0, 1);
  vfd.print("characters: ");
}

void loop() {

  // Display open heart.
  vfd.setCursor(13, 1);
  vfd.write((char)0);
  delay(750);

  // Display closed heart for shorter period.
  vfd.setCursor(13, 1);
  vfd.write((char)1);
  delay(250);
}
