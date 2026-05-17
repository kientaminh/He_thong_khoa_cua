#ifndef _LCD_H_
#define _LCD_H_

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "../Password/password.h"
#include <Keypad.h>

extern LiquidCrystal_I2C lcd;

void LCD_Init();

void LCD_Clear();

void LCD_SetCursor(uint8_t col, uint8_t row);

void LCD_Print(uint8_t col, uint8_t row, String text);

void LCD_ShowWelcome();

void LCD_ShowLocked();

void LCD_ShowUnlocked();

void LCD_ShowWrongPassword();

void LCD_ShowFingerprintOK();

void LCD_ShowFingerprintFail();

void LCD_ShowEnterPassword();
#endif