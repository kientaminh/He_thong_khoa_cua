#include "fingerprint.h"

/*
    AS608
    VCC - 3V3
    TX - 16
    RX - 17
*/
// Khởi tạo đối tượng HardwareSerial
HardwareSerial mySerial(2);

// Khởi tạo đối tượng Adafruit_Fingerprint
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void Fingerprint_Init() 
{
    //Nut xoa van tay
    pinMode(BUTTON, INPUT_PULLUP);
    mySerial.begin(57600, SERIAL_8N1, FINGERPRINT_RX_PIN, FINGERPRINT_TX_PIN);
    finger.begin(57600);
    // Khởi tạo cảm biến vân tay
    if (finger.verifyPassword()) 
    {
        Serial.println("Found fingerprint sensor!");
    } 
    else 
    {
        Serial.println("Did not find fingerprint sensor :(");
        while (1) { delay(1); }
    }
    Serial.println(F("Reading sensor parameters"));
    finger.getParameters();
    Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
    Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
    Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
    Serial.print(F("Security level: ")); Serial.println(finger.security_level);
    Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
    Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
    Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

}

void Fingerprint_Enroll(uint8_t id)
{
    int p = -1;
    LCD_Clear();
    LCD_Print(0, 0, "Dang ky tay");
    LCD_Print(0, 1, "Dat ngon tay");
    /*
        Quet lan 1
    */
    while (p != FINGERPRINT_OK) 
    {
        p = finger.getImage();
        switch (p) 
        {
            case FINGERPRINT_OK:
                LCD_Clear();
                LCD_Print(0, 0, "Da quet lan 1");
            break;
            case FINGERPRINT_NOFINGER:
                Serial.print(".");
            break;
            case FINGERPRINT_PACKETRECIEVEERR:
                Serial.println("Loi ket noi");
                LCD_Clear();
                LCD_Print(0, 0, "Loi ket noi");
            return;
            case FINGERPRINT_IMAGEFAIL:
                Serial.println("Loi cam bien");
                LCD_Clear();
                LCD_Print(0, 0, "Loi cam bien");
            return;
            default:
                Serial.println("Loi khong ro");
                LCD_Clear();
                LCD_Print(0, 0, "Loi khong ro");
            break;
        }
    }

    // OK success!

    p = finger.image2Tz(1);
    if (p != FINGERPRINT_OK)
    {
        LCD_Clear();
        LCD_Print(0, 0, "Anh loi");
        return;
    }

    /*
        Nha ngon tay
    */
    LCD_Clear();
    LCD_Print(0, 0, "Nha ngon tay");

    delay(2000);

    p = 0;
    while (p != FINGERPRINT_NOFINGER) 
    {
        p = finger.getImage();
    }
    /*
        Dat lai tay
    */
    LCD_Clear();
    LCD_Print(0, 0, "Dat lai tay");
    Serial.print("ID "); 
    Serial.println(id);
    p = -1;
    while (p != FINGERPRINT_OK) 
    {
        p = finger.getImage();
        switch (p) 
        {
            case FINGERPRINT_OK:
                Serial.println("Da quet lan 2");
                LCD_Clear();
                LCD_Print(0, 0, "Da quet lan 2");
                break;
            case FINGERPRINT_NOFINGER:
                Serial.print(".");
                delay(50);
                break;
            case FINGERPRINT_PACKETRECIEVEERR:
                Serial.println("Loi ket noi");
                LCD_Clear();
                LCD_Print(0, 0, "Loi ket noi");
                return;
            case FINGERPRINT_IMAGEFAIL:
                Serial.println("Loi cam bien");
                LCD_Clear();
                LCD_Print(0, 0, "Loi cam bien");
                return;
            default:
                Serial.println("Loi khong ro");
                LCD_Clear();
                LCD_Print(0, 0, "Loi khong ro");
                return;
        }
    }

    // OK success!

    p = finger.image2Tz(2);
    if (p != FINGERPRINT_OK)
    {
        LCD_Clear();
        LCD_Print(0, 0, "Anh loi");
        return;
    }

    /*
        kiem tra khop
    */
    Serial.println(id);
    p = finger.createModel();
    if (p == FINGERPRINT_OK) 
    {
        Serial.println("Trung khop");
        LCD_Clear();
        LCD_Print(0, 0, "Trung khop");
    } 
    else
    {
        LCD_Clear();
        LCD_Print(0, 0, "Khong trung");
        return;
    }
    /*
        Luu van tay
    */
    Serial.print("ID "); 
    Serial.println(id);
    p = finger.storeModel(id);
    if (p == FINGERPRINT_OK)
    {
        LCD_Clear();

        LCD_Print(0, 0, "Luu thanh cong");
        LCD_Print(0, 1, "ID: " + String(id));
    }
    else
    {
        LCD_Clear();
        LCD_Print(0, 0, "Luu that bai");
    }

    delay(2000);
}
uint8_t Fingerprint_InputID()
{
    char key;

    LCD_Clear();
    LCD_Print(0, 0, "Nhap vi tri luu");
    
    while(1)
    {
        key = Keypad_GetKey();
        if (key)
        {
            // Neu nhan so
            if (key >= '1' && key <= '9')
            {
                LCD_Clear();
    
                LCD_Print(0, 0, "ID:");
                LCD_Print(4, 0, String(key));
                return key - '0';
            }
            
        }
    }
}
void Fingerprint_Check()
{
    int p = finger.getImage();

    // Khong co ngon tay
    if (p != FINGERPRINT_OK)
    {
        return;
    }

    // Chuyen anh thanh du lieu
    p = finger.image2Tz();

    if (p != FINGERPRINT_OK)
    {
        LCD_Clear();
        LCD_Print(0, 0, "Doc tay loi");

        delay(1000);

        LCD_Clear();
        LCD_ShowEnterPassword();

        return;
    }

    // Tim van tay
    p = finger.fingerFastSearch();

    if (p == FINGERPRINT_OK)
    {
        // Tim thay
        LCD_Clear();

        LCD_Print(0, 0, "Mo cua");

        LCD_Print(0, 1, "ID: " + String(finger.fingerID));

        openDoor();
        Buzzer_OpenDoor();
        delay(1000);

        closeDoor();
    }
    else
    {
        // Khong tim thay
        LCD_Clear();

        LCD_Print(0, 0, "Khong hop le");
        Buzzer_WrongPassword();
        delay(500);
    }

    LCD_Clear();

    LCD_ShowWelcome();
}

void Fingerprint_Delete(uint8_t id)
{
    LCD_Clear();
    LCD_Print(0, 0, "Dang xoa tay");

    int p = finger.deleteModel(id);
    if (p == FINGERPRINT_OK)
    {
        LCD_Clear();
        LCD_Print(0, 0, "Xoa thanh cong");
        LCD_Print(0, 1, "ID: " + String(id));
    }
    else
    {
        LCD_Clear();
        LCD_Print(0, 0, "Xoa that bai");
    }

    delay(1500);

    LCD_Clear();
    LCD_ShowWelcome();
}