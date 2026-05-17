#include "password.h"

String correctPassword = "1234";
String inputPassword = "";

void Password_Init()
{
    // Sau này load EEPROM ở đây
}

bool Password_Check(String input)
{
    return (input == correctPassword);
}


String Password_Get()
{
    return correctPassword;
}

void enterPassword(char key)
{
    if (key)
    {
        Buzzer_Beep(100);
        LCD_ShowEnterPassword();
        // Xóa ký tự
        if (key == '*')
        {
            if (inputPassword.length() > 0)
            {
                inputPassword.remove(inputPassword.length() - 1);
                LCD_Print(0, 1, "                ");
                LCD_Print(0, 1, inputPassword);
            }
        }
        // Nhập số
        else if (key >= '0' && key <= '9')
        {
            inputPassword += key;
            LCD_Print(0, 1, "                ");
            LCD_Print(0, 1, inputPassword);
            if (inputPassword.length() >= 4)
            {
                if (Password_Check(inputPassword))
                {
                    LCD_ShowUnlocked();
                    openDoor();
                    Buzzer_OpenDoor();
                    delay(1000);
                    closeDoor();
                }
                else
                {
                    LCD_ShowWrongPassword();
                    Buzzer_WrongPassword();
                    delay(500);
                }
                // Reset password
                inputPassword = "";
                LCD_Clear();
                LCD_ShowWelcome();
            }
        }
    }
}