#ifndef LCD_H
#define LCD_H

#include "stm32f10x.h"

// LCD control pins
#define LCD_RS_PIN GPIO_Pin_0
#define LCD_RW_PIN GPIO_Pin_1
#define LCD_E_PIN  GPIO_Pin_2
#define LCD_CTRL_PORT GPIOA

// LCD data pins
#define LCD_D4_PIN GPIO_Pin_8
#define LCD_D5_PIN GPIO_Pin_9
#define LCD_D6_PIN GPIO_Pin_10
#define LCD_D7_PIN GPIO_Pin_11
#define LCD_DATA_PORT GPIOA

// Function Prototypes
void LCD_InitPins(void);
void LCD_Begin(uint8_t cols, uint8_t rows);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t col, uint8_t row);
void LCD_Print(const char* str); // Change char* to const char*
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);

#endif // LCD_H

