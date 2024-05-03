#include <Arduino.h>

// Include for the LED's
#include <Adafruit_NeoPixel.h>

#define PIN A2
#define NUMPIXELS 13

#define GENERAL 150, 150, 150
#define DIM 5, 5, 5
#define PURPLE 150, 0, 150
#define GOLD 168, 67, 0
#define ORANGE 168, 47, 0
#define BLUE 0, 92, 168
#define GREEN 0, 168, 0
#define RED 168, 0, 0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int colorUpdate = 0; // Flag for updating colors
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

// Setup OLED
Adafruit_SSD1306 display(128, 32, &Wire, 13);
String textBuffer = "";

// Scroll Text setup
int x, x2, minX;

// Mode Button Variables
int modePushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

// Keyboard Mapping and initialization
const int ModeButton = A0;

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

// Is discord muted?
bool discMute = false;
bool discDeafen = false;

// Function Declarations
void checkModeButton();
void writeToDisplay(String toWrite, int size);
void scrollText(String toWrite, int size);
void setPixelMode();
void setAllPixels(int r, int g, int b);
void setPixelColor(int pixel, int r, int g, int b);
void toggleMute();
void toggleDeafen();

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextWrap(false);
  x = 0; // Setup the scrolling text whenever it is used (Draw it offscreen)

  pinMode(ModeButton, INPUT_PULLUP);
  Keyboard.begin();

  // Turn off the TX LED.
  pinMode(LED_BUILTIN_TX, INPUT);
  pixels.begin();
}

void loop()
{
  char key = keypad.getKey();
  checkModeButton();
  setPixelMode();
  switch (modePushCounter)
  {
  case 0:
    scrollText("General", 4);
    switch (key)
    {
    case '1':
      // Discord Mute Microphone
      Keyboard.press(KEY_F13);
      toggleMute();
      break;
    case '2':
      // Discord Deafen
      Keyboard.press(KEY_F14);
      toggleDeafen();
      break;
    case '3':
      // Discord Screen Share
      Keyboard.press(KEY_F15);
      break;
    case '4':
      // Discord Overlay
      Keyboard.press(KEY_F16);
      break;
    case '5':
      //
      break;
    case '6':
      //
      break;
    case '7':
      //
      break;
    case '8':
      //
      break;
    case '9':
      //
      break;
    case '0':
      //
      break;
    case 'A':
      //
      break;
    case 'B':
      // Focus/Unfocus Desktop
      Keyboard.press(WIN);
      Keyboard.print('d');
      break;
    }
    delay(10);
    Keyboard.releaseAll();
    break;
  case 1:
    scrollText("Starfield", 4);
    switch (key)
    {
    case '1':
      // Discord Mute Microphone
      Keyboard.press(KEY_F13);
      toggleMute();
      break;
    case '2':
      // Discord Deafen
      Keyboard.press(KEY_F14);
      toggleDeafen();
      break;
    case '3':
      // Discord Screen Share
      Keyboard.press(KEY_F15);
      break;
    case '4':
      // Discord Overlay
      Keyboard.press(KEY_F16);
      break;
    case '5':
      //
      break;
    case '6':
      // Add system power
      Keyboard.press(KEY_UP_ARROW);
      break;
    case '7':
      //
      break;
    case '8':
      // Screen snippet
      Keyboard.press(WIN);
      Keyboard.press(SHIFT);
      Keyboard.print('s');
      break;
    case '9':
      // System to the left
      Keyboard.press(KEY_LEFT_ARROW);
      break;
    case '0':
      // Decrease system power
      Keyboard.press(KEY_DOWN_ARROW);
      break;
    case 'A':
      // System to the right
      Keyboard.press(KEY_RIGHT_ARROW);
      break;
    case 'B':
      // Focus/Unfocus Desktop
      Keyboard.press(WIN);
      Keyboard.print('d');
      break;
    }
    delay(10);
    Keyboard.releaseAll();
    break;
  case 2:
    scrollText("Mode 2", 4);
    switch (key)
    {
    case '1':
      //
      break;
    case '2':
      //
      break;
    case '3':
      //
      break;
    case '4':
      //
      break;
    case '5':
      //
      break;
    case '6':
      //
      break;
    case '7':
      //
      break;
    case '8':
      //
      break;
    case '9':
      //
      break;
    case '0':
      //
      break;
    case 'A':
      //
      break;
    case 'B':
      //
      break;
    }
    delay(10);
    Keyboard.releaseAll();
    break;
  case 3:
    scrollText("Mode 3", 4);
    switch (key)
    {
    case '1':
      //
      break;
    case '2':
      //
      break;
    case '3':
      //
      break;
    case '4':
      //
      break;
    case '5':
      //
      break;
    case '6':
      //
      break;
    case '7':
      //
      break;
    case '8':
      //
      break;
    case '9':
      //
      break;
    case '0':
      //
      break;
    case 'A':
      //
      break;
    case 'B':
      //
      break;
    }
    delay(10);
    Keyboard.releaseAll();
    break;
  }
  delay(1);
}

void scrollText(String toWrite, int size)
{
#define SPACER 2 * size * 6; // 2 spaces * the Text Size * 6 Pixels for a normal character

  if (toWrite != textBuffer)
  { // This makes sure the scroll doesn't get reset for every call in loop()
    x = 0;
    x2 = x + (toWrite.length() * size * 6) + SPACER; // Add a copy of the text to the right of the original
  }
  textBuffer = toWrite;

  display.clearDisplay();
  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x, 0); // Draw the first string
  display.print(toWrite);
  display.setCursor(x2, 0); // Draw the second string
  display.print(toWrite);
  display.display();

  minX = -6 * size * toWrite.length();
  // If the first string goes off the left, draw it off screen at the same distance the second string was
  if (--x < minX)
    x = x2 + (toWrite.length() * size * 6) + SPACER;
  // If the second string goes off the left, draw it off screen at the same distance the first string was
  if (--x2 < minX)
    x2 = x + (toWrite.length() * size * 6) + SPACER;
}

void checkModeButton()
{
  buttonState = digitalRead(ModeButton);
  if (buttonState != lastButtonState)
  {
    if (buttonState == LOW)
    {
      modePushCounter++;
      colorUpdate = 0;
    }
    delay(50);
  }
  lastButtonState = buttonState;
  if (modePushCounter > 3)
  {
    modePushCounter = 0;
  }
}

void setPixelMode()
{
  if (colorUpdate == 0)
  {
    switch (modePushCounter)
    {
    case 0:
      // General
      setAllPixels(DIM);
      setPixelColor(0, GENERAL);
      discMute ? setPixelColor(1, RED) : setPixelColor(1, PURPLE);
      discDeafen ? setPixelColor(2, RED) : setPixelColor(2, PURPLE);
      setPixelColor(3, PURPLE);
      setPixelColor(4, PURPLE);
      setPixelColor(12, RED);
      pixels.show();
      break;
    case 1:
      // Starfield
      setAllPixels(DIM);
      setPixelColor(0, GENERAL);
      discMute ? setPixelColor(1, RED) : setPixelColor(1, PURPLE);
      discDeafen ? setPixelColor(2, RED) : setPixelColor(2, PURPLE);
      setPixelColor(3, PURPLE);
      setPixelColor(4, PURPLE);
      setPixelColor(6, BLUE);
      setPixelColor(8, GENERAL);
      setPixelColor(9, BLUE);
      setPixelColor(10, BLUE);
      setPixelColor(11, BLUE);
      setPixelColor(12, RED);
      pixels.show();
      break;
    case 2:
      // Unused
      setAllPixels(DIM);
      setPixelColor(0, GENERAL);
      pixels.show();
      break;
    case 3:
      // Unused
      setAllPixels(DIM);
      setPixelColor(0, GENERAL);
      pixels.show();
      break;
    }
    colorUpdate = 1;
  }
}

void setAllPixels(int r, int g, int b)
{
  for (int i = 0; i < 14; i++)
  {
    setPixelColor(i, r, g, b);
  }
}

void setPixelColor(int pixel, int r, int g, int b)
{
  pixels.setPixelColor(pixel, pixels.Color(r, g, b));
}

void toggleMute()
{
  discMute ? discMute = false : discMute = true;
  colorUpdate = 0;
}

void toggleDeafen()
{
  discDeafen ? discDeafen = false : discDeafen = true;
  colorUpdate = 0;
}