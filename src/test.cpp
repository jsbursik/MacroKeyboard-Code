// Example program
#include <iostream>
#include <string>

using namespace std;

typedef void (*arrFunc)();

// macro to turn 2D char array into a string
#define makeKeymap(x) ((char *)x)

const int ROWS = 3;
const int COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', '4'},
    {'5', '6', '7', '8'},
    {'9', '0', 'A', 'B'},
};

void printOne() { cout << "One" << endl; }
void printKeymap() { cout << makeKeymap(keys) << endl; }
void printTwo() { cout << "Two" << endl; }
void printThree() { cout << "Three" << endl; }

const int SIZE = 2;

arrFunc functions[SIZE][SIZE] = {
    {printOne, printKeymap},
    {printTwo, printThree},
};

int main()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      functions[i][j]();
    }
  }
}
