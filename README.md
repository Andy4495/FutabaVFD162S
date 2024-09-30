# FutabaVFD162S Library

[![Arduino Compile Sketches](https://github.com/Andy4495/FutabaVFD162S/actions/workflows/arduino-compile-sketches.yml/badge.svg)](https://github.com/Andy4495/FutabaVFD162S/actions/workflows/arduino-compile-sketches.yml)
[![Check Markdown Links](https://github.com/Andy4495/FutabaVFD162S/actions/workflows/check-links.yml/badge.svg)](https://github.com/Andy4495/FutabaVFD162S/actions/workflows/check-links.yml)

This is an improved version of the [FutabaUsVfd][1] library published on Arduino Playground. It is designed to work with the Futaba US162SD03 Vacuum Fluorescent Display. It may work with other VFDs using the same controller chips.

## Library Usage

_Be sure to review the example sketches included with the library._

1. Include the library:

   ```cpp
   #include <FutabaVFD162S.h>
   ```

2. Instantiate an object, passing in the Arduino pin numbers used to control the display:

   ```cpp
   FutabaVFD162S vfd(CLK_pin_number, DATA_pin_number, RESET_pin_number);
   ```

3. Initialize the vfd object:

   ```cpp
   vfd.begin(number_of_columns, number_of_rows);
   ```

   The Futaba 162SD03 has 16 columns and 2 rows, so it would normally be initialized with:

   ```cpp
   vfd.begin(16,2)
   ```

4. Call the supported library methods to display information similar to the way you would use the LiquidCrystal library.

## Modifications from original library

- Updated directory structure and added `library.properties` to conform to the [Arduino library specification][3].
- Changed ``#include "WProgram.h"`` to `#include "Arduino.h"`
- Changed `virtual void write(uint8_t character)` to `virtual size_t write(uint8_t character)`
- Renamed example sketch extensions from `.pde` to `.ino`
- Added methods (see [datasheet][2] for details):

  ```cpp
  void setBrightness(uint8_t level);
  void setCursorModeAutoInc(); // Auto-increment cursor each time character is printed (default)
  void setCursorModeAutoDec(); // Auto-decrement cursor each time character is printed
  void setCursorModeNonInc();  // Cursor stays at same position when character is printed
  void setFlashPositions(uint8_t start, uint8_t stop); // Several ranges can be chosen with multiple calls and may overlap
  void setFlashModeEnabled();
  void setFlashModeDisabled();
  void setFlashRate50(); // 50 Hz; Effectively makes characters look 1/2 as bright as non-flashing characters
  void setFlashRate1();  // Default rate
  void setFlashRateTenth(); // 1/10 Hz
  void setFontWestern();
  void setFontKatakana();
  void setNonBufferedMode();  // Default
  void setBufferedMode();
  void printMessageBuffer();
  ```

- Updated timing delay definitions to slightly higher than datasheet specifications to account for system clock frequency errors across a wide range of devices:

  ```cpp
  static const uint8_t HALF_PERIOD_TIME = 25;  // Datasheet specifies 20 us (40 us clock period, TCLOCK)
  static const uint8_t DATA_SETUP_TIME = 5;    // Datasheet specifies 3 us (tsu)
  static const uint8_t PROCESS_TIME = 25;      // Datasheet specifies 25 us (tprocess)
  static const uint8_t RESET_HOLD_TIME = 50;   // Datasheet specifies 30 us (twRST). This parameter seemed to be most sensitive to specfic minimal timing.
  static const uint16_t POST_RESET_DELAY_TIME = 2500;  // Datasheet specifies 2000 us (twait)
  ```

## Using the 162SD03 Module

The Arduino Playground [article][1] mentions that the [162SD03][2] module has problems with flicker. My observation is that while there is some flicker with brightness levels lower than 40, I was not able to notice any flicker anytime the brightness level was set to 40 or more.

There is a noticeable difference in brightness when going from level 254 to 255. This is a much bigger change than any of the other single-value changes.

I measured supply current of around 320 mA when the device was powered, regardless of whether something was displayed or the screen was blank. The datasheet specs it at 450 mA typical, 600 mA maximum.

While the 162SD03 is a 5V device, the CLK, DATA, and RESET inputs are compatible with 3.3V logic levels.

Pin Functions (J1):

1. Vcc
2. CLK
3. GND
4. DATA
5. RESET

## References

- Original FutabaUsVfd [library][1] at Arduino Playground.
- Futaba Model US162SD03 Vacuum Fluorescent Display [datasheet][2]

## License

The software and other files in this repository are released under what is commonly called the [MIT License][100]. See the file [`LICENSE`][101] in this repository.

[1]: https://playground.arduino.cc/Main/FutabaUsVfd/
[2]: ./extras//VFD-162.pdf
[3]: https://arduino.github.io/arduino-cli/latest/library-specification/
[100]: https://choosealicense.com/licenses/mit/
[101]: ./LICENSE
[//]: # ([200]: https://github.com/Andy4495/FutabaVFD162S)
