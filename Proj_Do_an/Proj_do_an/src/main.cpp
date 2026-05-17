#include "../lib/Keypad/pad.h"
#include "../lib/Lcd/lcd.h"
#include "../lib/Fingerprint/fingerprint.h"
#include "../lib/Relay/relay.h"
#include "../lib/Password/password.h"
#include "../lib/Buzzer/buzzer.h"

void setup() 
{
    Serial.begin(115200);
    
    LCD_Init();
    Keypad_Init();
    Relay_Init();
    Fingerprint_Init();
    Buzzer_Init();

    LCD_ShowWelcome();
    delay(500);
}

void loop() 
{
    char key = Keypad_GetKey();

    // Khong quet van tay khi dang thao tac
    if (digitalRead(BUTTON) == HIGH && key != '#')
    {
        Fingerprint_Check();
    }

    // Xoa van tay
    if (digitalRead(BUTTON) == LOW)
    {
        delay(50);

        while (digitalRead(BUTTON) == LOW);

        uint8_t id = Fingerprint_InputID();

        Fingerprint_Delete(id);

        LCD_Clear();
        LCD_ShowWelcome();

        return;
    }

    // Dang ky van tay
    if (key == '#')
    {
        delay(150);

        uint8_t id = Fingerprint_InputID();

        Fingerprint_Enroll(id);

        LCD_Clear();
        LCD_ShowWelcome();

        return;
    }

    // Password
    enterPassword(key);
}