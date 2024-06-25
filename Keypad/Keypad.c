#include "keypad.h"

/* Declare a global variable to store the key pressed */
uint8 global_KeyPad_Key = 0;


/* Function to initialize the keypad columns and rows */
void keypad_Init(void){
    /* Initialize the columns state */
    uint8 column;
    for(column = KEYPAD_COLUMNS_START_PIN; column < (KEYPAD_COLUMNS_START_PIN + KEYPAD_NUMBER_OF_COLUMNS); column++){
        /* Configure the column pins as inputs with pull-up resistors */
        Gpio_ConfigPin(KEYPAD_ROWS_PORT , column , GPIO_INPUT , GPIO_PULL_UP);
    }

    /* Initialize the rows state */
    uint8 row;
    for(row = KEYPAD_ROWS_START_PIN; row < (KEYPAD_ROWS_START_PIN + KEYPAD_NUMBER_OF_ROWS); row++){
        /* Configure the row pins as outputs */
        Gpio_ConfigPin(KEYPAD_ROWS_PORT , row , GPIO_OUTPUT , GPIO_PUSH_PULL);
        /* Set the initial state of the row pins to BUTTON_RELEASED */
        Gpio_WritePin(KEYPAD_ROWS_PORT , row , BUTTON_RELEASED);
    }
}


/* Function to scan the keypad and update the global_KeyPad_Key variable if a key is pressed */
void keypad_Manage(void){
    uint8 column;
    uint8 row;
    for(row = KEYPAD_ROWS_START_PIN; row < (KEYPAD_ROWS_START_PIN + KEYPAD_NUMBER_OF_ROWS); row++){
        /* Set the current row pin to BUTTON_PRESSED */
        Gpio_WritePin(KEYPAD_ROWS_PORT , row , BUTTON_PRESSED);
        for(column = KEYPAD_COLUMNS_START_PIN; column < (KEYPAD_COLUMNS_START_PIN + KEYPAD_NUMBER_OF_COLUMNS); column++){
            /* Check if any of the column pins are pressed */
            if(Gpio_ReadPin(KEYPAD_COLUMNS_PORT , column) == BUTTON_PRESSED){
                /* Debounce the key press by waiting for a short period of time */
                for(unsigned i =0;i<10000;i++);
                /* Check if the key is still pressed after debouncing */
                if(Gpio_ReadPin(KEYPAD_COLUMNS_PORT , column) == BUTTON_PRESSED){
                    /* Map the row and column numbers to a single number and update the global variable */
                    global_KeyPad_Key = ((row - KEYPAD_ROWS_START_PIN) * KEYPAD_NUMBER_OF_COLUMNS) + (column - KEYPAD_COLUMNS_START_PIN);
                    /* Notify any registered callback function that a key has been pressed */
                    KeypadCallouts_KeyPressNotificaton();
                }
            }
        }
        /* Set the current row pin to BUTTON_RELEASED */
        Gpio_WritePin(KEYPAD_ROWS_PORT , row , BUTTON_RELEASED);
    }
}


/* Function to return the value of the key last pressed */
uint8 keypad_GetKey(void){
    return global_KeyPad_Key + 1; /* Add 1 to the value to get the correct key number */
}
