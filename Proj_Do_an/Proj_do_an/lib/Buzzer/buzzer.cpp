#include "buzzer.h"

void Buzzer_Init()
{
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

void Buzzer_On()
{
    digitalWrite(BUZZER_PIN, HIGH);
}

void Buzzer_Off()
{
    digitalWrite(BUZZER_PIN, LOW);
}

void Buzzer_Beep(int timeMs)
{
    Buzzer_On();
    delay(timeMs);
    Buzzer_Off();
}

void Buzzer_OpenDoor()
{
    // Bip bip khi mo cua
    Buzzer_Beep(100);
    delay(100);
    Buzzer_Beep(100);
}

void Buzzer_WrongPassword()
{
    // Keu dai khi sai
    Buzzer_On();
    delay(500);
    Buzzer_Off();
}