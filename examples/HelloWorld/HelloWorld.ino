/*
  FutabaUsVfd Library - Hello World

 Demonstrates the use an Futaba VFD. Tested
 with model US162SD03CB 2x16  display.

 This sketch prints "Hello World!" to the VFD
 and shows the number of seconds since the sketch
 started.

  The circuit:

 * Display +5v (pin 1) & GND (pin 3) connected to regulated 5v, 500ma power supply.
 * Display GND   (pin 3) also connected to Arduino ground.
 * Display Clock (pin 2) connected to Arduino/MSP pin 5.
 * Display Data  (pin 4) connected to Arduino/MSP pin 6.
 * Display Reset (pin 5) connected to Arduino/MSP pin 8.

 Created Mar 17, 2011.

 This example code is in the public domain.

 http://arduino.cc/playground/Main/FutabaUsVfd

 Slight modification Nov 2019 to include in updated library at https://github.com/Andy4495/FutabaUsVfd

*/

// Include the library code.
#include <FutabaUsVfd.h>

FutabaUsVfd vfd(5, 6, 8);

void setup() {
  // Set up the VFD's number of columns and rows:
  vfd.begin(16, 2);
  // Print a message to the VFD.
  vfd.print("hello, world!");
}

void loop() {
  // Set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  vfd.setCursor(0, 1);
  // Print the number of seconds since reset:
  vfd.print(millis()/1000);

  delay(1000);
}
