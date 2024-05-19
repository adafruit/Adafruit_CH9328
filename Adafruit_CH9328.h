/**
 * @file Adafruit_CH9328.h
 * @brief Library for interfacing with the CH9328 UART to HID Keyboard chip.
 *
 * This library provides functionality to interface with the CH9328 chip using
 * Arduino. It supports sending key presses via a transparent key-mode that
 * mimics a USB HID keyboard device. The library allows for sending of
 * individual key presses as well as string typing with automatic handling of
 * upper/lower case and punctuation.
 *
 * @author Limor Fried (Ladyada)
 */

#ifndef Adafruit_CH9328_h
#define Adafruit_CH9328_h

#include "Adafruit_CH9328_USKeymap.h" // Include the keymap for convenience
#include "Arduino.h"

///< Class for interfacing with the CH9328 in "Transparent Mode"
class Adafruit_CH9328 {
public:
  Adafruit_CH9328();
  void begin(Stream *stream);
  void sendKeyPress(byte keys[6], byte modifier = 0);
  void typeString(const char *str);

private:
  Stream *_stream;
  void writeCommand(byte *command, byte commandLength);
  byte getModifier(char c);
  byte getKeyCode(char c);
};

#endif // Adafruit_CH9328_h
