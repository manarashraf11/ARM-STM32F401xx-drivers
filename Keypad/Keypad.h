#include "Gpio.h"
#include "Std_Types.h"

#ifndef STD_TYPES_H_ // Header guard to prevent multiple inclusion
#define STD_TYPES_H_



/* Column configurations */
#define KEYPAD_COLUMNS_PORT       GPIO_B   // Set the GPIO port for the keypad columns
#define KEYPAD_COLUMNS_START_PIN  0        // Set the starting pin for the keypad columns
#define KEYPAD_NUMBER_OF_COLUMNS  3        // Set the number of keypad columns

/* Row configurations */
#define KEYPAD_ROWS_PORT          GPIO_B  // Set the GPIO port for the keypad rows
#define KEYPAD_ROWS_START_PIN     5       // Set the starting pin for the keypad rows
#define KEYPAD_NUMBER_OF_ROWS     4       // Set the number of keypad rows

typedef enum{
	BUTTON_PRESSED , BUTTON_RELEASED
}button_state;


#define COL_PORT GPIO_B
#define COL_START_INDEX 0
#define COL_END_INDEX 2



#define KEYPAD_MAX_COLS 3
#define KEYPAD_MAX_ROWS 4

#define KEYPAD_BUTTON_PRESSED 0
#define KEYPAD_BUTTON_RELEASE 1

//#define uint8 key 0

void keypad_Init(void);

void keypad_Manage(void);

uint8 keypad_GetKey(void);

void KeypadCallouts_KeyPressNotificaton();



#endif
