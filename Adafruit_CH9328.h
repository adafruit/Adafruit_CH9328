/**
 * @file Adafruit_CH9328.h
 * @brief Library for interfacing with the CH9328 UART to HID Keyboard chip.
 *
 * This library provides functionality to interface with the CH9328 chip using Arduino. It supports
 * sending key presses via a transparent key-mode that mimics a USB HID keyboard device. The library
 * allows for sending of individual key presses as well as string typing with automatic handling of
 * upper/lower case and punctuation.
 *
 * @author Limor Fried (Ladyada)
 * @license MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef Adafruit_CH9328_h
#define Adafruit_CH9328_h

#include "Arduino.h"
#include "Adafruit_CH9328_USKeymap.h"  // Include the keymap for convenience

class Adafruit_CH9328 {
public:
    Adafruit_CH9328();
    void begin(Stream *stream);
    void sendKeyPress(byte keys[6], byte modifier = 0);
    void typeString(const char *str);

private:
    Stream *_stream;
    void writeCommand(byte* command, byte commandLength);
    byte getModifier(char c);
    byte getKeyCode(char c);
};

#endif // Adafruit_CH9328_h
