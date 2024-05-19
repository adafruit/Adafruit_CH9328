/* 
 *  This demo is for the "transparent transmission" mode #3 which you can enter by 
 *  setting the Adafruit CH9328 switches so that #2 is OFF, and #3 and #4 are ON
 *  In this mode you can send 'raw' HID key commands for more complex keypress combos!
 */
#include <Adafruit_CH9328.h>

Adafruit_CH9328 keyboard;

// Uncomment these lines if you need to use SoftwareSerial because there's no Serial1 device
//#include <SoftwareSerial.h>
//SoftwareSerial Serial1(3, 2); // RX, TX pins

void setup() {
  // Start the debug serial port, wait till it opens
  Serial.begin(115200);
  while (!Serial) delay(100);

  // The default baud rate for the CH9328 is 9600
  Serial1.begin(9600);
  keyboard.begin(&Serial1);

  // Sending "Hello World!" as an ASCII character string
  keyboard.typeString("Hello World!");

  // Wait for 1 second
  delay(1000);

  // Send the backspace key 12 times to erase the string
  byte keys[6] = {KEY_BACKSPACE, 0, 0, 0, 0, 0}; // Keycode for backspace in US mapping
  byte noKeysPressed[6] = {0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 12; i++) {
    keyboard.sendKeyPress(keys, 0);          // Press &
    keyboard.sendKeyPress(noKeysPressed, 0); // Release the key
  }
}

void loop() {
}
