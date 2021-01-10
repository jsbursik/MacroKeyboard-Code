#include <Arduino.h>

// Include the necessary keyboard stuff
#include <Keyboard.h>
#include <Keypad.h>

// Keyboard Definitions
#define CTRL  KEY_LEFT_CTRL
#define ALT   KEY_LEFT_ALT
#define SHIFT KEY_LEFT_SHIFT

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

char keys[ROWS][COLS]= {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','0','A','B'},
};

byte rowPins[ROWS] = {4,5,A3};
byte colPins[COLS] = {6,7,8,9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Function Declarations
void checkModeButton();
void writeToDisplay(String toWrite, int size);
void scrollText(String toWrite, int size);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextWrap(false);
  x = display.width(); // Setup the scrolling text whenever it is used (Draw it offscreen)
  
  pinMode(ModeButton, INPUT_PULLUP);
  Keyboard.begin();

  // Turn off the TX LED.
  pinMode(LED_BUILTIN_TX, INPUT);
}

void loop() {
  char key = keypad.getKey();
  checkModeButton();
  switch(modePushCounter){
    case 0:
      scrollText("General", 4);
      switch(key){
        case '1': 
          // Discord Mute Microphone
          Keyboard.press(CTRL);
          Keyboard.press(ALT);
          Keyboard.print('1');
          break;
        case '2': 
          // Discord Deafen
          Keyboard.press(CTRL);
          Keyboard.press(ALT);
          Keyboard.print('2');
          break;
        case '3': 
          // Discord Screen Share
          Keyboard.press(CTRL);
          Keyboard.press(ALT);
          Keyboard.print('3');
          break;
        case '4': 
          // Open/Switch to Discord
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.print('3');
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
      delay(10); Keyboard.releaseAll();
      break;
    case 1:
      scrollText("VSCode", 4);
      switch(key){
        case '1':
          // Open Command Panel
          Keyboard.press(CTRL); 
          Keyboard.press(SHIFT);
          Keyboard.print('p');
          break;
        case '2': 
          // Open Terminal
          Keyboard.press(CTRL);
          Keyboard.print('`'); 
          break;
        case '3': 
          // Toggle Comment line
          Keyboard.press(CTRL);
          Keyboard.print('/'); 
          break;
        case '4':
          // Toggle Comment Block 
          Keyboard.press(SHIFT);
          Keyboard.press(ALT);
          Keyboard.print('a');
          break;
        case '5': 
          // Split editor Vertical
          Keyboard.press(CTRL);
          Keyboard.print('\\'); 
          break;
        case '6': 
          // Split editor Orthogonal
          Keyboard.press(CTRL);
          Keyboard.print('k');
          Keyboard.print('\\'); 
          break;
        case '7':
          // Fold all regions
          Keyboard.press(CTRL);
          Keyboard.print('k');
          Keyboard.print('0');
          break;
        case '8': 
          // Unfold all regions
          Keyboard.press(CTRL);
          Keyboard.print('k');
          Keyboard.print('j');
          break;
        case '9':
          // Go to beginning of line 
          Keyboard.press(KEY_HOME);
          break;
        case '0': 
          // Go to ending of line
          Keyboard.press(KEY_END);
          break;
        case 'A': 
          // Go to beginning of file
          Keyboard.press(CTRL);
          Keyboard.press(KEY_HOME);
          break;
        case 'B': 
          // Go to ending of file
          Keyboard.press(CTRL);
          Keyboard.press(KEY_END);
          break;
      }
      delay(10); Keyboard.releaseAll();
      break;
    case 2:
      scrollText("World of Warcraft", 4);
      switch(key){
        case '1': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('1');
          break;
        case '2': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('2');
          break;
        case '3': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('3');
          break;
        case '4': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('4');
          break;
        case '5': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('5');
          break;
        case '6': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('6');
          break;
        case '7': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('7');
          break;
        case '8': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('8');
          break;
        case '9': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('8');
          break;
        case '0': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('0');
          break;
        case 'A': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('-');
          break;
        case 'B': 
          Keyboard.press(CTRL);
          Keyboard.press(SHIFT);
          Keyboard.print('=');
          break;
      }
      delay(10); Keyboard.releaseAll();
      break;
    case 3:
      scrollText("Mode 3", 4);
      switch(key){
        case '1': Keyboard.println("Mode 3, key 1"); break;
        case '2': Keyboard.println("Mode 3, key 2"); break;
        case '3': Keyboard.println("Mode 3, key 3"); break;
        case '4': Keyboard.println("Mode 3, key 4"); break;
        case '5': Keyboard.println("Mode 3, key 5"); break;
        case '6': Keyboard.println("Mode 3, key 6"); break;
        case '7': Keyboard.println("Mode 3, key 7"); break;
        case '8': Keyboard.println("Mode 3, key 8"); break;
        case '9': Keyboard.println("Mode 3, key 9"); break;
        case '0': Keyboard.println("Mode 3, key 0"); break;
        case 'A': Keyboard.println("Mode 3, key A"); break;
        case 'B': Keyboard.println("Mode 3, key B"); break;
      }
      delay(10); Keyboard.releaseAll();
      break;
  }
  delay(1);
}

void writeToDisplay(String toWrite, int size){
  if(toWrite != textBuffer){
    display.clearDisplay();
    display.setCursor(0,12);
    display.setTextSize(size);
    display.setTextColor(SSD1306_WHITE);
    display.print(toWrite);
    display.display();
  }
  textBuffer = toWrite;
}

void scrollText(String toWrite, int size){
  #define SPACER  2 * size * 6; // 2 spaces * the Text Size * 6 Pixels for a normal character
  if(toWrite != textBuffer){
    x = display.width(); // On a mode switch, always bring the text in from the right
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
  // If the first string goes completely off the left, draw it off screen at the same distance the second string was
  if(--x < minX) x = x2 + (toWrite.length() * size * 6) + SPACER;
  // If the second string goes off the left, draw it off screen at the same distance the first string was
  if(--x2 < minX) x2 = x + (toWrite.length() * size * 6) + SPACER;
}

void checkModeButton(){
  buttonState = digitalRead(ModeButton);
  if(buttonState != lastButtonState){
    if(buttonState == LOW){
      modePushCounter++;
    }
    delay(50);
  }
  lastButtonState = buttonState;
  if (modePushCounter > 3){
    modePushCounter = 0;
  }
}