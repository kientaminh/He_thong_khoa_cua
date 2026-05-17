#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <Arduino.h>
#define BUZZER_PIN 4

void Buzzer_Init();

void Buzzer_On();
void Buzzer_Off();

void Buzzer_Beep(int timeMs);
void Buzzer_OpenDoor();
void Buzzer_WrongPassword();

#endif