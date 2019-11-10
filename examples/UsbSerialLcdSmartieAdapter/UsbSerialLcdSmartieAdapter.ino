/*
  FutabaUsVfd Library - LCD Smartie Adapter

  Demonstrates the use an Futaba VFD. Tested
  with model US162SD03CB 2x16  display.

  Uses the Arduino as an adapter to allow
  a PC running LCD Smartie or LCDProc to
  display on the VFD.

  Configure LCD Smartie to use the
  diplay plugin crystal.dll and startup
  parameters as Arduino COM port,19200,1
  for example:

    COM3,19200,1

  For LCDProc, edit the server .conf file
  (most folks use LCDd.conf). In the
  [server] section set Driver=CFontz and in
  the [CFontz] set Device=<usb serial device>
  (usually Device=/dev/ttyUSB0), Size=20x4,
  Speed=19200 and NewFirmware=no. Other
  [CFontz] settings can be left at defaults.

  The circuit:

 * Display +5v (pin 1) & GND (pin 3) connected to regulated 5v, 500ma power supply.
 * Display GND   (pin 3) also connected to Arduino ground.
 * Display Clock (pin 2) connected to Arduino/MSP pin 5.
 * Display Data  (pin 4) connected to Arduino/MSP pin 6.
 * Display Reset (pin 5) connected to Arduino/MSP pin 8.

 Created Mar 17, 2011.
 Based of UsbSerialLcdSmartieAdapter from Ncr7454Vfd library.

 This example code is in the public domain.

 http://arduino.cc/playground/Main/FutabaUsVfd
*/

// Include the library code.
#include <FutabaUsVfd.h>

FutabaUsVfd vfd(5, 6, 8);

uint8_t serialGetCharacter() {

  while (!Serial.available()) {
  }

  Serial.read();
}

void handleCustomCharacter()
{
  uint8_t characterIndex = serialGetCharacter();
  uint8_t pixels[8];

  for (uint8_t i=0; i<8; i++)
  {
    // Character pixel rows.
    pixels[i] = serialGetCharacter() & 0b11111;
  }

  vfd.createChar(characterIndex, pixels);
}

void handleCrystalControlCode(uint8_t character) {

  switch (character)
  {
  case 3:
    // Restore display.
    // Not sure what this is but we'll enable our display.

    // NOT SUPPORTED.
    //vfd.display();
    break;

  case 4:
    // Turn off cursor.

    // NOT SUPPORTED.
    //vfd.noCursor();
    break;

  case 12:
    // Clear screen.
    vfd.clear();
    break;

  case 14: // Set brightness.
  case 15: // Set contrast, range 0-100.
    serialGetCharacter(); // Not implemented: read and discard byte.
    break;

  case 17:
    {
      // Set position.
      vfd.setCursor(serialGetCharacter(), serialGetCharacter());
      break;
    }

  case 19:
    // Turn on scroll.

    // NOT SUPPORTED.
    //vfd.verticalScroll();
    break;

  case 20:
    // Turn off scroll.

    // NOT SUPPORTED.
    //vfd.noVerticalScroll();
    break;

  case 22:
    // Disable scrolling marquee.
    // Not sure how many bytes, but LCD Smartie is sending 3 more
    // so read and discard all
    serialGetCharacter();
    serialGetCharacter();
    serialGetCharacter();
    break;

  case 23: // Wrap on.
  case 24: // Wrap off.
    // Ignore, display always wraps.
    break;

  case 25:
    // Set custom character pixels.
    handleCustomCharacter();
    break;

  case 26:
    // Init display.
    vfd.begin(16, 2);
    break;

    // Pass standard ASCII control codes straight through.
  case 8:
  case 9:
  case 10:
  case 13:
    vfd.write(character);
    break;

  default:
    // Unknown code, ignore it.
    break;
  }
}

void setup() {

  // Set up the VFD's number of columns and rows:
  vfd.begin(16, 2);

  // Initialize the serial connection.
  Serial.begin(19200);
}

void loop() {

  uint8_t character = serialGetCharacter();

  if (character < 32)
  {
    handleCrystalControlCode(character);
  }
  else
  {
    // Make any necessary character adjustments.

    if (character>=128 && character<(128+8))
    {
      character -= 128;
    }

    // Remap selected extended characters.
    switch (character)
    {
      case 0xDE:
        // Up arrow.
        character = 0xE0;
        break;

      case 0xE0:
        // Down arrow.
        character = 0xE1;
        break;

      case 0xE1:
        // Left arrow.
        character = 0xE2;
        break;

      case 0xDF:
        // Right arrow.
        character = 0xE3;
        break;

      case 0xFF:
        // Filled block.
        character = 0x7F;
        break;

      default:
        // Leave unchanged.
        break;
    }

    // Write the adjusted character.
    vfd.write(character);
  }
}
