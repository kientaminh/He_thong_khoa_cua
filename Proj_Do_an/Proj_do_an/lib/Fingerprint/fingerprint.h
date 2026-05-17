#ifndef _FINGERPRINT_H_
#define _FINGERPRINT_H_

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal_I2C.h>
#include "../Lcd/lcd.h"
#include "../Buzzer/buzzer.h"

// Khai báo chân kết nối cảm biến vân tay
#define FINGERPRINT_RX_PIN 16
#define FINGERPRINT_TX_PIN 17
#define BUTTON 15   //xoa van tay
extern uint8_t id;

void Fingerprint_Init();
void Fingerprint_Enroll(uint8_t id);
uint8_t Fingerprint_InputID();
void Fingerprint_Check();
void Fingerprint_Delete(uint8_t id);
#endif