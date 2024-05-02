#include "ScreenHelp.h"
#include <U8g2lib.h>
#include "bitmaps.h"
#include "Global.h"
#include <Wire.h>

int currentBitmap = 1;

// Create the display object
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void setupDisplay()
{
    Wire1.setSCL(ScreeniicClock);
    Wire1.setSDA(ScreeniicData);
    Wire1.begin();

    pinMode(pinButton1, INPUT_PULLDOWN);
    pinMode(pinButton2, INPUT_PULLDOWN);

    // Initialize the display
    // u8g2.begin();
}

void checkButtonPresses()
{
    static unsigned long lastDebounceTime1 = 0;
    static unsigned long lastDebounceTime2 = 0;
    static bool lastButtonState1 = HIGH;
    static bool lastButtonState2 = HIGH;
    bool currentButtonState1 = digitalRead(pinButton1);
    bool currentButtonState2 = digitalRead(pinButton2);
    // Serial.print(currentButtonState1);
    // Serial.println(currentButtonState2);

    if (currentButtonState1 != lastButtonState1)
    {
        lastDebounceTime1 = millis();
    }

    if (currentButtonState2 != lastButtonState2)
    {
        lastDebounceTime2 = millis();
    }

    if ((millis() - lastDebounceTime1) > 50)
    {
        if (currentButtonState1 == LOW)
        {
            switch (currentBitmap)
            {
            case 1:
                // Send GPS coordinates and Alert signal
                sharedData.helpMessage[0] = '1';
                currentBitmap++;
                // changeBitmap();
            case 2:
                sharedData.helpMessage[1] = '1';
                currentBitmap++;
                // changeBitmap();
            case 3:
                sharedData.helpMessage[2] = '1';
                currentBitmap++;
                // changeBitmap();
            case 4:
                sharedData.helpMessage[3] = '1';
                currentBitmap++;
                // changeBitmap();
            case 5:
                sharedData.helpMessage[4] = '1';
                currentBitmap++;
                // changeBitmap();
            case 6:
                sharedData.helpMessage[5] = '1';
                currentBitmap++;
                // changeBitmap();
            }
        }
    }

    if ((millis() - lastDebounceTime2) > 50)
    {
        if (currentButtonState2 == LOW)
        {
            switch (currentBitmap)
            {
            case 1:
                // Send GPS coordinates and Alert signal
                sharedData.helpMessage[0] = '1';
                currentBitmap++;
                // changeBitmap();
            case 2:
                sharedData.helpMessage[1] = '0';
                currentBitmap++;
                changeBitmap();
            case 3:
                sharedData.helpMessage[2] = '0';
                currentBitmap++;
                // changeBitmap();
            case 4:
                sharedData.helpMessage[3] = '0';
                currentBitmap++;
                // changeBitmap();
            case 5:
                sharedData.helpMessage[4] = '0';
                currentBitmap++;
                // changeBitmap();
            case 6:
                sharedData.helpMessage[5] = '0';
                currentBitmap++;
                // changeBitmap();
            }
        }

        lastButtonState1 = currentButtonState1;
        lastButtonState2 = currentButtonState2;
    }
}

void changeBitmap()
{
    u8g2.clearBuffer(); // clear the internal memory

    switch (currentBitmap)
    {
    case 1:
        u8g2.drawXBM(0, 0, BITMAP_WIDTH, BITMAP_HEIGHT, epd_bitmap_CanHelp_perguntas_inicio);
        break;
    case 2:
        u8g2.drawXBM(0, 0, BITMAP_WIDTH, BITMAP_HEIGHT, epd_bitmap_CanHelp_perguntas_1);
        break;
    // Add more cases as needed
    case 3:
        u8g2.drawXBM(0, 0, BITMAP_WIDTH, BITMAP_HEIGHT, epd_bitmap_CanHelp_perguntas_2);
        break;
    case 4:
        u8g2.drawXBM(0, 0, BITMAP_WIDTH, BITMAP_HEIGHT, epd_bitmap_CanHelp_perguntas_3);
        break;
    case 5:
        u8g2.drawXBM(0, 0, BITMAP_WIDTH, BITMAP_HEIGHT, epd_bitmap_CanHelp_perguntas_4);
        break;
    case 6:
        u8g2.drawXBM(0, 0, BITMAP_WIDTH, BITMAP_HEIGHT, epd_bitmap_CanHelp_perguntas_5);
    }

    u8g2.sendBuffer(); // transfer internal memory to the display
}
