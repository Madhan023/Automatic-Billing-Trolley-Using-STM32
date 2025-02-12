#include "stm32f10x.h"    
#include "delay.h"
#include "spi1.h"
#include "MFRC522.h"
#include "lcd.h"
#include <stdint.h>
#include <string.h> // For memcmp and strcpy
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include <stdio.h>

#define LED1_PIN GPIO_Pin_13
#define LED1_PORT GPIOC
#define LED2_PIN GPIO_Pin_14
#define LED2_PORT GPIOC

uint8_t cardID[5];
uint8_t num1, num2, num3, num4, num5;

// Card IDs
uint8_t card1ID[5] = {0x24, 0xff, 0xcc, 0xdc, 0xcb};
uint8_t card2ID[5] = {0x33, 0x84, 0xe1, 0x26, 0x70};
uint8_t card3ID[5] = {0x73, 0xb2, 0x16, 0x25, 0xf2};
uint8_t card4ID[5] = {0x53, 0xec, 0x44, 0x25, 0xde};
uint8_t card5ID[5] = {0x53, 0x84, 0x1a, 0x25, 0xe8};

// Item details
const char itemName1[] = "Chocolate";
int itemPrice1 = 15;
const char itemName2[] = "Milk";
int itemPrice2 = 50;
const char itemName3[] = "Biscuit";
int itemPrice3 = 35;
const char itemName4[] = "Juice";
int itemPrice4 = 30;
const char itemName5[] = "Lays";
int itemPrice5 = 20;

// Totals
int totalAmount = 0;

// Track scanned items
int item1Scanned = 0;
int item2Scanned = 0;
int item3Scanned = 0;
int item4Scanned = 0;
int item5Scanned = 0;

void LED_Init(void) {
    // Enable GPIOC clock for LEDs
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Configure PC13 as output push-pull for LED1
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = LED1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_PORT, &GPIO_InitStructure);

    // Configure PC14 as output push-pull for LED2
    GPIO_InitStructure.GPIO_Pin = LED2_PIN;
    GPIO_Init(LED2_PORT, &GPIO_InitStructure);
}

void LED_Blink(GPIO_TypeDef* LED_PORT, uint16_t LED_PIN) {
    // Turn on LED
    GPIO_SetBits(LED_PORT, LED_PIN);
    delay(500); // Delay for 100ms
    // Turn off LED
    GPIO_ResetBits(LED_PORT, LED_PIN);
    delay(500); // Delay for 100ms
}

void LCD_Init(void) {
    // Initialize LCD (assuming lcd.h provides the necessary functions)
    LCD_InitPins();
    LCD_Begin(16, 2); // Assuming a 16x2 LCD
}

void DisplayWelcomeMessage(void) {
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Print("Welcome to");
    LCD_SetCursor(0, 1);
    LCD_Print("Super Market");
    delay(3000); // Display for 3 seconds
}

void DisplayAddItemMessage(void) {
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Print("Add your item");
}

void DisplayItemAdded(const char* itemName) {
    char buffer[32]; // Adjust size if needed
    snprintf(buffer, sizeof(buffer), "%s Added", itemName); // Combine itemName and "Added" into one string
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Print(buffer); // Print the combined string
    delay(1000); // Display for 2 seconds
}

void DisplayItemRemoved(const char* itemName) {
    char buffer[32]; // Adjust size if needed
    snprintf(buffer, sizeof(buffer), "%s Removed", itemName); // Combine itemName and "Added" into one string
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Print(buffer); // Print the combined string
    delay(1000); // Display for 2 seconds
}

void DisplayTotalAmount(void) {
    char buffer[16];
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Print("Total Amount:");
    LCD_SetCursor(0, 1);
    sprintf(buffer, "%d Rs", totalAmount);
    LCD_Print(buffer);
}

int main(void) {
    SysTick_Config(SystemCoreClock / 1000);
    SPI1_InitPort();
    SPI1_Setup();
    SPI1_NSSdisable();
    SPI1_Enable();
    LED_Init();  // Initialize LED GPIOs
    LCD_Init();  // Initialize LCD
    MFRC522_Init();
    MFRC522_AntennaOn();
    
    DisplayWelcomeMessage();
    DisplayAddItemMessage();
    
    while (1) {
        if (MFRC522_Check(cardID) == MI_OK) {
            if (memcmp(cardID, card1ID, 5) == 0) {
                if (item1Scanned == 0) {
										LED_Blink(LED1_PORT, LED1_PIN);
                    DisplayItemAdded(itemName1);
                    totalAmount += itemPrice1;
                    item1Scanned = 1;
                    
                } else {
										LED_Blink(LED2_PORT, LED2_PIN);
                    DisplayItemRemoved(itemName1);
                    totalAmount -= itemPrice1;
                    item1Scanned = 0;
                    
                }
            } else if (memcmp(cardID, card2ID, 5) == 0) {
                if (item2Scanned == 0) {
										LED_Blink(LED1_PORT, LED1_PIN);
                    DisplayItemAdded(itemName2);
                    totalAmount += itemPrice2;
                    item2Scanned = 1;
                    
                } else {
										LED_Blink(LED2_PORT, LED2_PIN);
                    DisplayItemRemoved(itemName2);
                    totalAmount -= itemPrice2;
                    item2Scanned = 0;
                    
                }
            } else if (memcmp(cardID, card3ID, 5) == 0) {
                if (item3Scanned == 0) {
										LED_Blink(LED1_PORT, LED1_PIN);
                    DisplayItemAdded(itemName3);
                    totalAmount += itemPrice3;
                    item3Scanned = 1;
                    
                } else {
										LED_Blink(LED2_PORT, LED2_PIN);
                    DisplayItemRemoved(itemName3);
                    totalAmount -= itemPrice3;
                    item3Scanned = 0;
                    
                }
            }
						else if (memcmp(cardID, card4ID, 5) == 0) {
                if (item4Scanned == 0) {
										LED_Blink(LED1_PORT, LED1_PIN);
                    DisplayItemAdded(itemName4);
                    totalAmount += itemPrice4;
                    item4Scanned = 1;
                    
                } else {
										LED_Blink(LED2_PORT, LED2_PIN);
                    DisplayItemRemoved(itemName4);
                    totalAmount -= itemPrice4;
                    item4Scanned = 0;
                    
                }
            }
						else if (memcmp(cardID, card5ID, 5) == 0) {
                if (item5Scanned == 0) {
										LED_Blink(LED1_PORT, LED1_PIN);
                    DisplayItemAdded(itemName5);
                    totalAmount += itemPrice5;
                    item5Scanned = 1;
                    
                } else {
										LED_Blink(LED2_PORT, LED2_PIN);
                    DisplayItemRemoved(itemName5);
                    totalAmount -= itemPrice5;
                    item5Scanned = 0;
                    
                }
            }
            DisplayTotalAmount();
            delay(100);
        }
    }
}