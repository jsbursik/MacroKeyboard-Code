#include <Arduino.h>

// Include for LED's
#include <Adafruit_NeoPixel.h>

#define PIN A2
#define NUMPIXELS 13

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

#ifdef __AVR__
#include <avr/power.h>
#endif

// Include the necessary keyboard stuff
#include <Keyboard.h>
#include <Keypad.h>

// Simplifying key names
#define CTRL KEY_LEFT_CTRL
#define ALT KEY_LEFT_ALT
#define SHIFT KEY_LEFT_SHIFT
#define WIN KEY_LEFT_GUI

// Include stuff for display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

// Setup OLED - Width, Height, &Wire?, Reset pin?
Adafruit_SSD1306 display(128, 32, &Wire, 13);

// Keyboard mapping
const int MODEBUTTON = A0;

const byte ROWS = 3;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', '4'},
    {'5', '6', '7', '8'},
    {'9', '0', 'A', 'B'},
};

byte rowPins[ROWS] = {4, 5, A3};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  // Turn off onboard TX LED
  pinMode(LED_BUILTIN_TX, INPUT);
  // Pull up the voltage for the display, 0x3C is the I2C address for the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Stop wrapping text for scrolling text effect
  display.setTextWrap(false);
  // Init NeoPixels
  pixels.begin();
  // Init Keyboard
  Keyboard.begin();
  // Pull up MODEBUTTON, I'm not entirely sure why
  pinMode(MODEBUTTON, INPUT_PULLUP);
}
