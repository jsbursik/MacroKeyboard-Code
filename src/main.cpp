#include <Arduino.h>

// Include the necessary keyboard stuff
#include <Keyboard.h>
#include <Keypad.h>

// Include stuff for display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

// Setup OLED
Adafruit_SSD1306 display(128, 32, &Wire, 13);

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

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  writeToDisplay("Macro Keyboard v2", 2);
  delay(3000);

  pinMode(ModeButton, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  char key = keypad.getKey();
  checkModeButton();
  switch(modePushCounter){
    case 0:
      writeToDisplay("Mode 0", 2);
      switch(key){
        case '1': Keyboard.println("Mode 0, key 1"); break;
        case '2': Keyboard.println("Mode 0, key 2"); break;
        case '3': Keyboard.println("Mode 0, key 3"); break;
        case '4': Keyboard.println("Mode 0, key 4"); break;
        case '5': Keyboard.println("Mode 0, key 5"); break;
        case '6': Keyboard.println("Mode 0, key 6"); break;
        case '7': Keyboard.println("Mode 0, key 7"); break;
        case '8': Keyboard.println("Mode 0, key 8"); break;
        case '9': Keyboard.println("Mode 0, key 9"); break;
        case '0': Keyboard.println("Mode 0, key 0"); break;
        case 'A': Keyboard.println("Mode 0, key A"); break;
        case 'B': Keyboard.println("Mode 0, key B"); break;
      }
      delay(50); Keyboard.releaseAll();
      break;
    case 1:
      writeToDisplay("Mode 1", 2);
      switch(key){
        case '1': Keyboard.println("Mode 1, key 1"); break;
        case '2': Keyboard.println("Mode 1, key 2"); break;
        case '3': Keyboard.println("Mode 1, key 3"); break;
        case '4': Keyboard.println("Mode 1, key 4"); break;
        case '5': Keyboard.println("Mode 1, key 5"); break;
        case '6': Keyboard.println("Mode 1, key 6"); break;
        case '7': Keyboard.println("Mode 1, key 7"); break;
        case '8': Keyboard.println("Mode 1, key 8"); break;
        case '9': Keyboard.println("Mode 1, key 9"); break;
        case '0': Keyboard.println("Mode 1, key 0"); break;
        case 'A': Keyboard.println("Mode 1, key A"); break;
        case 'B': Keyboard.println("Mode 1, key B"); break;
      }
      delay(50); Keyboard.releaseAll();
      break;
    case 2:
      writeToDisplay("Mode 2", 2);
      switch(key){
        case '2': Keyboard.println("Mode 2, key 2"); break;
        case '1': Keyboard.println("Mode 2, key 1"); break;
        case '3': Keyboard.println("Mode 2, key 3"); break;
        case '4': Keyboard.println("Mode 2, key 4"); break;
        case '5': Keyboard.println("Mode 2, key 5"); break;
        case '6': Keyboard.println("Mode 2, key 6"); break;
        case '7': Keyboard.println("Mode 2, key 7"); break;
        case '8': Keyboard.println("Mode 2, key 8"); break;
        case '9': Keyboard.println("Mode 2, key 9"); break;
        case '0': Keyboard.println("Mode 2, key 0"); break;
        case 'A': Keyboard.println("Mode 2, key A"); break;
        case 'B': Keyboard.println("Mode 2, key B"); break;
      }
      delay(50); Keyboard.releaseAll();
      break;
    case 3:
      writeToDisplay("Mode 3", 2);
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
      delay(50); Keyboard.releaseAll();
      break;
  }
  delay(1);
}

void writeToDisplay(String toWrite, int size){
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);
  display.print(toWrite);
  display.display();
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