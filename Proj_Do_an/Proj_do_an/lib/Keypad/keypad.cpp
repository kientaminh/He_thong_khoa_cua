#include "pad.h"

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

byte rowPins[ROWS] = {
    13,
    12,
    14,
    27
};

byte colPins[COLS] = {
    26,
    25,
    33
};

Keypad keypad = Keypad(
    makeKeymap(keys),
    rowPins,
    colPins,
    ROWS,
    COLS
);


void Keyprint() 
{
    char key = keypad.getKey();

    if (key) 
    {
        Serial.print("Pressed: ");
        Serial.println(key);
    }
}
void Keypad_Init()
{
    String inputPassword = "";
}

char Keypad_GetKey()
{
    return keypad.getKey();
}
