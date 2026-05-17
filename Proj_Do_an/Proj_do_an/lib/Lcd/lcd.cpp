#include "lcd.h"

/*
    Lcd 16x02
    Dia chi 0x27
*/
LiquidCrystal_I2C lcd(0x27, 16, 2);

void LCD_Init()
{
    lcd.init();

    lcd.backlight();

    lcd.clear();
}

void LCD_Clear()
{
    lcd.clear();
}

void LCD_SetCursor(uint8_t col, uint8_t row)
{
    lcd.setCursor(col, row);
}

void LCD_Print(uint8_t col, uint8_t row, String text)
{
    lcd.setCursor(col, row);

    lcd.print(text);
}

void LCD_ShowWelcome()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(" SMART LOCK");

    lcd.setCursor(0, 1);
    lcd.print(" Ready...");
}

void LCD_ShowLocked()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("DOOR LOCKED");
}

void LCD_ShowUnlocked()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Mo cua");
}

void LCD_ShowWrongPassword()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Khong hop le");
}

void LCD_ShowFingerprintOK()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("FINGERPRINT OK");
}

void LCD_ShowFingerprintFail()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("FINGERPRINT FAIL");
}

void LCD_ShowEnterPassword()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("ENTER PASSWORD");

    lcd.setCursor(0, 1);
}