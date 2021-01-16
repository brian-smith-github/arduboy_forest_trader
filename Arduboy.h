#include <SPI.h>
// Choose which board to compile for in the next 2 lines.....

#define ARDUBOY_10   //< compile for the production Arduboy v1.0
//#define AB_DEVKIT    //< compile for the official dev kit

#define CLK   13
#define MOSI  11

//-------------------------------------------------------------
#ifdef AB_DEVKIT
#define CS		6
#define DC		4
#define RST		12

#define PIN_LEFT_BUTTON 9
#define PIN_RIGHT_BUTTON 5
#define PIN_UP_BUTTON 8
#define PIN_DOWN_BUTTON 10
#define PIN_A_BUTTON A0
#define PIN_B_BUTTON A1
// map all LEDs to the single TX LED on DEVKIT
#define RED_LED 17
#define GREEN_LED 17
#define BLUE_LED 17
#define TX_LED 17
#define RX_LED 17

//-------------------------------------------------------------
#else
#define CS 12
#define DC 4
#define RST 6

#define PIN_LEFT_BUTTON A2
#define PIN_RIGHT_BUTTON A1
#define PIN_UP_BUTTON A0
#define PIN_DOWN_BUTTON A3
#define PIN_A_BUTTON 7
#define PIN_B_BUTTON 8

#define RED_LED 10
#define GREEN_LED 11
#define BLUE_LED 9
#define TX_LED 30
#define RX_LED 17

#endif
