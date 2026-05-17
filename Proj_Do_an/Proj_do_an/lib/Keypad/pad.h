#ifndef _PAD_H_
#define _PAD_H_

#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "../Password/password.h"
#include "../Buzzer/buzzer.h"

extern Keypad keypad;
void Keyprint();
void Keypad_Init();

char Keypad_GetKey();


#endif