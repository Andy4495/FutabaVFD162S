/*
  FutabaUsVfd Library - Declaration file

  Originally created 17 March 2011

  This file is in the public domain.
*/

#ifndef FutabaUsVfd_h
#define FutabaUsVfd_h

#include <inttypes.h>
#include "Print.h"
#include "Arduino.h"

class FutabaUsVfd : public Print {
public:

  // Special control characters supported by display. See datasheet for more information.
  // Send using writeCharacterDirect(), not write().
  static const uint8_t CLEAR_ENTIRE_DISPLAY_CHARACTER = 0x01; // Clears display and homes cursor.
  static const uint8_t SET_CURSOR_POSITION_CHARACTER = 0x02; // Second character specifies cursor position.
  static const uint8_t SET_CURSOR_MODE_CHARACTER = 0x03; // Second character is cursor increment mode.
  static const uint8_t SET_DISPLAY_BRIGHTNESS_CHARACTER = 0x04; // Second character is display brightness.
  static const uint8_t SET_INPUT_OUTPUT_MODE_CHARACTER = 0x05; // Second character specifies I/O mode.
  static const uint8_t SET_FLASH_POSITION_CHARACTER = 0x06; // Second and third characters specify flash range.
  static const uint8_t FLASH_MODE_CHARACTER = 0x07; // Second character specifies flashing on/off.
  static const uint8_t SET_FLASH_RATE_CHARACTER = 0x08; // Second character specifies flash rate.
  static const uint8_t SELECT_FONT_CHARACTER = 0x09; // Second character specifies font.
  static const uint8_t LOAD_USER_CHARACTER_CHARACTER = 0x0A; // Second character is index, next 5 pixel data.
  static const uint8_t SET_BUFFERED_MODE_CHARACTER = 0x0B; // Second byte is buffering mode.
  static const uint8_t PRINT_MESSAGE_BUFFER_CHARACTER = 0x0C; // Flush buffer and home cursor.

  FutabaUsVfd(uint8_t clockPin, uint8_t dataPin, uint8_t resetPin);

  // Sets the character dimensions of the display.
  void begin(uint8_t numColumns, int numRows);

  void clear();
  void home();

  // Methods supported by LiquidCrystal but not by our library.
//  void noBlink();
//  void blink();
//  void noCursor();
//  void cursor();
//  void noDisplay();
//  void display();
//  void scrollDisplayLeft();
//  void scrollDisplayRight();
//  void leftToRight();
//  void rightToLeft();
//  void autoscroll();
//  void noAutoscroll();
//  void createChar(uint8_t, uint8_t[]);
//  void command(uint8_t);

  void createChar(uint8_t characterIndex, uint8_t pixels[] /* 8 bytes, 1 for each row */);
  void setCursor(uint8_t column, uint8_t row);
  virtual size_t write(uint8_t character);

  // Methods unique to our class.
  void writeCharacterDirect(uint8_t character);
  void setBrightness(uint8_t level);
  // Cursor control
  // Changes do not take affect immediately; next character will be printed to current cursor postion before new mode takes affect.
  void setCursorModeAutoInc(); // Auto-increment cursor each time character is printed (default)
  void setCursorModeAutoDec(); // Auto-decrement cursor each time character is printed
  void setCursorModeNonInc();  // Cursor stays at same position when character is printed
  // Character flashing configuration
  void setFlashPositions(uint8_t start, uint8_t stop); // Several ranges can be chosen with multiple calls and may overlap
  void setFlashModeEnabled();
  void setFlashModeDisabled();
  void setFlashRate50(); // 50 Hz; Effectively makes characters look 1/2 as bright as non-flashing characters
  void setFlashRate1();  // Default rate
  void setFlashRateTenth(); // 1/10 Hz
  // Font selection
  void setFontWestern();
  void setFontKatakana();
  // Display buffer modes
  void setNonBufferedMode();  // Default
  void setBufferedMode();
  void printMessageBuffer();

private:

  // Hiding this for now so it is not used for resetPin. The display does not work reliably
  // without reset as it is quite easy to restart the Ardino sketch in the middle of sending
  // a character which throws the serial communications out of sync.
  static const uint8_t DO_NOT_USE_PIN = 0xFF;

  static const uint8_t NUM_CUSTOM_CHARACTERS = 0x08;
  static const uint8_t CUSTOM_CHARACTER_TRANSLATE_OFFSET = 0x18 - 0x00; // VFD custom characters start at 18h.

  static const uint8_t CHARACTER_PIXEL_WIDTH = 5;
  static const uint8_t CHARACTER_PIXEL_HEIGHT = 7;

  // Timing delays are in microseconds.
  // Define times slightly higher than datasheet specifications to account for system clock freq errors across a wide range of devices
  static const uint8_t HALF_PERIOD_TIME = 25;  // Datasheet specifies 20 us (40 us clock period, TCLOCK)
  static const uint8_t DATA_SETUP_TIME = 5;    // Datasheet specifies 3 us (tsu)
  static const uint8_t PROCESS_TIME = 25;      // Datasheet specifies 25 us (tprocess)
  static const uint8_t RESET_HOLD_TIME = 50;   // Datasheet specifies 30 us (twRST). This parameter seemed to be most sensitive to specfic minimal timing.
  static const uint16_t POST_RESET_DELAY_TIME = 2500;  // Datasheet specifies 2000 us (twait)

/*
  // Timing delays are in microseconds.
  static const uint8_t HALF_PERIOD_TIME = 20;
  static const uint8_t DATA_SETUP_TIME = 3;
  static const uint8_t PROCESS_TIME = 20;
  static const uint8_t RESET_HOLD_TIME = 30;
  static const uint16_t POST_RESET_DELAY_TIME = 2000;
  */

  uint8_t _clockPin;
  uint8_t _dataPin;
  uint8_t _resetPin;

  uint8_t _numDisplayColumns;
  uint8_t _numDisplayRows;
  uint8_t _numDisplayCharacters;

  inline void timingDelay(uint16_t delayInMicroseconds);
};

inline void FutabaUsVfd::timingDelay(uint16_t delayInMicroseconds)
{
  delayMicroseconds(delayInMicroseconds);
}

#endif // FutabaUsVfd_h
