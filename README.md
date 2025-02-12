# Automatic-Billing-Trolley-Using-STM32
Automatic Billing Trolley Using STM32
Project Overview
The Automatic Billing Trolley Using STM32 is a cutting-edge solution designed to automate the billing process in supermarkets. This project leverages RFID technology to identify items placed in the trolley, thereby eliminating the need for manual scanning and streamlining the checkout process.

Key Features
RFID Technology Integration:

Utilizes RFID tags to identify items. Each product in the supermarket is equipped with an RFID tag that holds a unique identifier.
STM32 Microcontroller:

The core of the system, responsible for processing RFID data, managing the display, and handling user interactions.
LCD Display:

Provides a user-friendly interface to display item names, prices, and the total billing amount.
LED Indicators:

Visual indicators to show the addition and removal of items from the trolley.
Real-Time Billing:

Automatically updates the total amount as items are added or removed, allowing for a seamless shopping experience.
How It Works
Initialization:

The system initializes the STM32 microcontroller, RFID reader, LCD display, and LED indicators.
Item Scanning:

When an item is placed in the trolley, the RFID reader identifies the tag and retrieves the item information.
The system compares the scanned RFID tag with the predefined list of item tags to determine the item details.
Billing Process:

The item name and price are displayed on the LCD.
The total amount is updated in real-time as items are added or removed.
LED indicators provide visual feedback indicating whether an item has been added or removed.
User Interaction:

The LCD display guides the user through the process, showing messages such as "Welcome to Super Market", "Add your item", "Item Added", "Item Removed", and the "Total Amount".
