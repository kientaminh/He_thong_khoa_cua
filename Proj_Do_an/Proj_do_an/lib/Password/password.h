#ifndef _PASSWORD_H_
#define _PASSWORD_H_

#include <Arduino.h>
#include "../Lcd/lcd.h"
#include "../Keypad/pad.h"
#include <Keypad.h>
#include "../Relay/relay.h"
#include "../Buzzer/buzzer.h"

extern String correctPassword;
extern String inputPassword;

void Password_Init();

bool Password_Check(String input);

String Password_Get();

void enterPassword(char key);
#endif