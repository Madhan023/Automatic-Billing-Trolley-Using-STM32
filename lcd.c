#include "lcd.h"
#include "delay.h" // Assume delay.h provides a delay function
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
void LCD_InitPins(void) {
    // Enable GPIOA clock for control and data pins
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    // Initialize control pins (RS, RW, E)
    GPIO_InitStructure.GPIO_Pin = LCD_RS_PIN | LCD_RW_PIN | LCD_E_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_CTRL_PORT, &GPIO_InitStructure);

    // Initialize data pins (D4, D5, D6, D7)
    GPIO_InitStructure.GPIO_Pin = LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN;
    GPIO_Init(LCD_DATA_PORT, &GPIO_InitStructure);
}

void LCD_Begin(uint8_t cols, uint8_t rows) {
    // Unused parameter warning fix
    (void)cols;
    (void)rows;

    // Initialize LCD
    delay(15); // Wait for more than 15ms after VDD rises to 4.5V

    LCD_SendCommand(0x02); // Initialize in 4-bit mode
    delay(1);

    // Function set: 4-bit/2-line
    LCD_SendCommand(0x28);
    delay(1);

    // Display ON, Cursor OFF, Blink OFF
    LCD_SendCommand(0x0C);
    delay(1);

    // Clear display
    LCD_SendCommand(0x01);
    delay(2);

    // Entry mode set: Increment automatically, No display shift
    LCD_SendCommand(0x06);
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01); // Clear display
    delay(2);              // Wait for the command to complete
}

void LCD_SetCursor(uint8_t col, uint8_t row) {
    uint8_t address = (row == 0 ? 0x00 : 0x40) + col;
    LCD_SendCommand(0x80 | address); // Set DDRAM address
}

void LCD_Print(const char* str) { // Change char* to const char*
    while (*str) {
        LCD_SendData(*str++);
    }
}

void LCD_SendCommand(uint8_t cmd) {
    GPIO_ResetBits(LCD_CTRL_PORT, LCD_RS_PIN); // RS = 0 for command
    GPIO_ResetBits(LCD_CTRL_PORT, LCD_RW_PIN); // RW = 0 for write

    // Send higher nibble
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D4_PIN, (cmd >> 4) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D5_PIN, (cmd >> 5) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D6_PIN, (cmd >> 6) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D7_PIN, (cmd >> 7) & 0x01);

    // Pulse the enable pin
    GPIO_SetBits(LCD_CTRL_PORT, LCD_E_PIN);
    delay(1);
    GPIO_ResetBits(LCD_CTRL_PORT, LCD_E_PIN);

    // Send lower nibble
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D4_PIN, (cmd >> 0) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D5_PIN, (cmd >> 1) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D6_PIN, (cmd >> 2) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D7_PIN, (cmd >> 3) & 0x01);

    // Pulse the enable pin
    GPIO_SetBits(LCD_CTRL_PORT, LCD_E_PIN);
    delay(1);
    GPIO_ResetBits(LCD_CTRL_PORT, LCD_E_PIN);

    delay(1); // Wait for the command to complete
}

void LCD_SendData(uint8_t data) {
    GPIO_SetBits(LCD_CTRL_PORT, LCD_RS_PIN); // RS = 1 for data
    GPIO_ResetBits(LCD_CTRL_PORT, LCD_RW_PIN); // RW = 0 for write

    // Send higher nibble
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D4_PIN, (data >> 4) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D5_PIN, (data >> 5) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D6_PIN, (data >> 6) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D7_PIN, (data >> 7) & 0x01);

    // Pulse the enable pin
    GPIO_SetBits(LCD_CTRL_PORT, LCD_E_PIN);
    delay(1);
    GPIO_ResetBits(LCD_CTRL_PORT, LCD_E_PIN);

    // Send lower nibble
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D4_PIN, (data >> 0) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D5_PIN, (data >> 1) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D6_PIN, (data >> 2) & 0x01);
    GPIO_WriteBit(LCD_DATA_PORT, LCD_D7_PIN, (data >> 3) & 0x01);

    // Pulse the enable pin
    GPIO_SetBits(LCD_CTRL_PORT, LCD_E_PIN);
    delay(1);
    GPIO_ResetBits(LCD_CTRL_PORT, LCD_E_PIN);

    delay(1); // Wait for the data to be written
}