#include <Adafruit_CH9328.h>

/**
 * @brief Constructor for the Adafruit_CH9328 class.
 */
Adafruit_CH9328::Adafruit_CH9328() {
}

/**
 * @brief Initializes the library with a pre-configured Stream object.
 * 
 * @param stream Pointer to the Stream object (e.g., Serial, SoftwareSerial)
 * already configured with the correct baud rate.
 */
void Adafruit_CH9328::begin(Stream *stream) {
  _stream = stream;
}

/**
 * @brief Sends a key press command to the CH9328 device.
 * 
 * @param keys Array of up to 6 key codes to be pressed simultaneously.
 * @param modifier Modifier key code (e.g., Shift, Ctrl) to be applied 
 * with the key presses.
 */
void Adafruit_CH9328::sendKeyPress(byte keys[6], byte modifier) {
  byte dataPacket[8] = {modifier, 0x00, 
                        keys[0], keys[1], keys[2], 
                        keys[3], keys[4], keys[5]};
  writeCommand(dataPacket, sizeof(dataPacket));
}

/**
 * @brief Types out a string by sending key press commands for each character,
 * handling upper/lower case and punctuation.
 * 
 * @param str Pointer to the character string to be typed out.
 */
void Adafruit_CH9328::typeString(const char *str) {
  byte noKeysPressed[6] = {0, 0, 0, 0, 0, 0};
  while (*str) {
    byte modifier = getModifier(*str);
    byte keyCode = getKeyCode(*str);
    byte keys[6] = {keyCode, 0, 0, 0, 0, 0};
    sendKeyPress(keys, modifier);
    sendKeyPress(noKeysPressed, 0); // Release all keys
    str++;
  }
}


/**
 * @brief Writes a command to the CH9328 via the provided Stream.
 * 
 * This method is private and used internally by other methods.
 * 
 * @param command Pointer to the array of bytes representing the command to be sent.
 * @param commandLength The number of bytes in the command array.
 */
void Adafruit_CH9328::writeCommand(byte* command, byte commandLength) {
  _stream->write(command, commandLength);
}

/**
 * @brief Gets the modifier key required for a specific character.
 * 
 * This method is private and used internally by the typeString method.
 * 
 * @param c The character for which the modifier key is determined.
 * @return byte The modifier key code (0 if no modifier is needed).
 */
byte Adafruit_CH9328::getModifier(char c) {
  if (isupper(c) || ispunct(c)) {
    return MODIFIER_KEY_LEFT_SHIFT;
  }
  return 0;
}

/**
 * @brief Gets the USB HID keycode for a specific character.
 * 
 * This method is private and used internally by the typeString method.
 * 
 * @param c The character to convert to a keycode.
 * @return byte The corresponding keycode, or 0 if the character does not have a direct keycode.
 */
byte Adafruit_CH9328::getKeyCode(char c) {
  // Mapping character to key code using ASCII values
  if (isalpha(c)) {
    // Handle alphabetic characters with offset from 'a' or 'A'
    return KEY_A + (tolower(c) - 'a');
  } else if (isdigit(c)) {
    // Handle numeric characters; numbers are continuous in ASCII from '0' to '9'
    return (c == '0') ? KEY_0 : KEY_1 + (c - '1');
  } else {
    // Handle punctuation and special characters explicitly
    switch (c) {
        case ' ': return KEY_SPACE;
        case '!': return KEY_1; // Shift is handled by getModifier
        case '@': return KEY_2; // Shift is handled by getModifier
        case '#': return KEY_3; // Shift is handled by getModifier
        case '$': return KEY_4; // Shift is handled by getModifier
        case '%': return KEY_5; // Shift is handled by getModifier
        case '^': return KEY_6; // Shift is handled by getModifier
        case '&': return KEY_7; // Shift is handled by getModifier
        case '*': return KEY_8; // Shift is handled by getModifier
        case '(': return KEY_9; // Shift is handled by getModifier
        case ')': return KEY_0; // Shift is handled by getModifier
        case '-': return KEY_MINUS;
        case '_': return KEY_MINUS; // Shift is handled by getModifier
        case '=': return KEY_EQUAL;
        case '+': return KEY_EQUAL; // Shift is handled by getModifier
        case '[': return KEY_LEFT_BRACE;
        case '{': return KEY_LEFT_BRACE; // Shift is handled by getModifier
        case ']': return KEY_RIGHT_BRACE;
        case '}': return KEY_RIGHT_BRACE; // Shift is handled by getModifier
        case '\\': return KEY_BACKSLASH;
        case '|': return KEY_BACKSLASH; // Shift is handled by getModifier
        case ';': return KEY_SEMICOLON;
        case ':': return KEY_SEMICOLON; // Shift is handled by getModifier
        case '\'': return KEY_QUOTE;
        case '"': return KEY_QUOTE; // Shift is handled by getModifier
        case ',': return KEY_COMMA;
        case '<': return KEY_COMMA; // Shift is handled by getModifier
        case '.': return KEY_PERIOD;
        case '>': return KEY_PERIOD; // Shift is handled by getModifier
        case '/': return KEY_SLASH;
        case '?': return KEY_SLASH; // Shift is handled by getModifier
        case '`': return KEY_TILDE;
        case '~': return KEY_TILDE; // Shift is handled by getModifier
        default:  return 0; // No valid keycode (or handle as needed)
    }
  }
}
