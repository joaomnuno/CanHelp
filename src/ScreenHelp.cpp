#include "ScreenHelp.h"
#include <U8g2lib.h> 
#include "bitmaps.h"

static int currentBitmap = 1;


// Create the display object
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, ScreeniicClock, ScreeniicData);


void setupDisplay() {
    pinMode(pinButton1, INPUT_PULLUP);
    pinMode(pinButton2, INPUT_PULLUP);

    // Initialize the display
    u8g2.begin();
}

void checkButtonPresses() {
    static unsigned long lastDebounceTime1 = 0;
    static unsigned long lastDebounceTime2 = 0;
    static bool lastButtonState1 = HIGH;
    static bool lastButtonState2 = HIGH;
    bool currentButtonState1 = digitalRead(pinButton1);
    bool currentButtonState2 = digitalRead(pinButton2);

    if (currentButtonState1 != lastButtonState1) {
        lastDebounceTime1 = millis();
    }

    if (currentButtonState2 != lastButtonState2) {
        lastDebounceTime2 = millis();
    }

    if ((millis() - lastDebounceTime1) > 50) {
        if (currentButtonState1 == LOW) {
            if (currentBitmap == 1){
                // Send GPS coordinates and Alert signal
                currentBitmap = 2;
                changeBitmap();
            }

        }
    }

    if ((millis() - lastDebounceTime2) > 50) {
        if (currentButtonState2 == LOW) {
            if (currentBitmap == 1){
                // Send GPS coordinates and Alert signal
                currentBitmap = 2;
                changeBitmap();
            }
        }
    }

    lastButtonState1 = currentButtonState1;
    lastButtonState2 = currentButtonState2;
}

void changeBitmap() {
    u8g2.clearBuffer(); // clear the internal memory

    switch (currentBitmap) {
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
            break;
    }

    u8g2.sendBuffer(); // transfer internal memory to the display
}



