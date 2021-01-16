// ARDUBOY VERSION
#include "Arduboy.h"

uint8_t readCapacitivePin(int pinToMgeasure);
uint8_t readCapXtal(int pinToMeasure);
volatile uint8_t *mosiport, *clkport, *csport, *dcport;
uint8_t mosipinmask, clkpinmask, cspinmask, dcpinmask;
bool scrolling;


// Routines to set and clear bits (used in the sleep code)
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


void core_init()
{
  SPI.begin();
  pinMode(MOSI, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(PIN_UP_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LEFT_BUTTON, INPUT_PULLUP);
  pinMode(PIN_RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(PIN_DOWN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_A_BUTTON, INPUT_PULLUP);
  pinMode(PIN_B_BUTTON, INPUT_PULLUP);
  
  csport      = portOutputRegister(digitalPinToPort(CS));
  cspinmask   = digitalPinToBitMask(CS);
  dcport      = portOutputRegister(digitalPinToPort(DC));
  dcpinmask   = digitalPinToBitMask(DC);
  // Setup reset pin direction (used by both SPI and I2C)  
  pinMode(RST, OUTPUT);
  digitalWrite(RST, HIGH);
  delay(1);       // VDD (3.3V) goes high at start, lets just chill for a ms
  digitalWrite(RST, LOW); // bring reset low
  delay(10);        // wait 10ms
  digitalWrite(RST, HIGH);  // bring out of reset
     *csport |= cspinmask;
    *dcport &= ~dcpinmask;
    *csport &= ~cspinmask;
  SPI.transfer(0xAE); // Display Off
  SPI.transfer(0XD5); // Set Display Clock Divisor v
  SPI.transfer(0xF0); //   0x80 is default 
  SPI.transfer(0xA8); // Set Multiplex Ratio v
  SPI.transfer(0x3F); //
  SPI.transfer(0xD3); // Set Display Offset v
  SPI.transfer(0x0);  //
  SPI.transfer(0x40); // Set Start Line (0)
  SPI.transfer(0x8D); // Charge Pump Setting v
  SPI.transfer(0x14); //   Enable
  SPI.transfer(0x20); // Set Memory Mode v
  SPI.transfer(0); //   Horizontal Addressing
  SPI.transfer(0x21); SPI.transfer(00); SPI.transfer(0x7f); 
  SPI.transfer(0x22); SPI.transfer(00); SPI.transfer(0x07);
  SPI.transfer(0xA1); // Set Segment Re-map (A0) | (b0001)
  SPI.transfer(0xC8); // Set COM Output Scan Direction
  SPI.transfer(0xDA); // Set COM Pins v
  SPI.transfer(0x12); //
  SPI.transfer(0x81); // Set Contrast v
  SPI.transfer(0xCF); //
  SPI.transfer(0xD9); // Set Precharge
  SPI.transfer(0xF1); //
  SPI.transfer(0xDB); // Set VCom Detect
  SPI.transfer(0x40); //
  SPI.transfer(0xA4); // Entire Display ON
  SPI.transfer(0xA6); // Set normal/inverse display
  SPI.transfer(0xAF); // Display On
  *csport |= cspinmask;
  
  // turn all the LEDs off...
  digitalWrite(TX_LED, 255);
  digitalWrite(RX_LED, 255);
 
  digitalWrite(RED_LED, 255);
  digitalWrite(GREEN_LED, 255);
  digitalWrite(BLUE_LED, 255);
}

void display_dataMode(void){
  
  *dcport |= dcpinmask;
  *csport &= ~cspinmask;
}
//-------------------------------------------------------------------------------------------------------------------

void display_init(int mode){
    *csport |= cspinmask;
    *dcport &= ~dcpinmask;
    *csport &= ~cspinmask;
  SPI.transfer(0x20); // Set Memory Mode v
  SPI.transfer(mode); //   Horizontal Addressing
  SPI.transfer(0x21); SPI.transfer(00); SPI.transfer(0x7f); 
  SPI.transfer(0x22); SPI.transfer(00); SPI.transfer(0x07);

  *csport |= cspinmask;

  display_dataMode();
}

//------------------------------
void ssd1306_xfer_start(void){
  *dcport |= dcpinmask;
  *csport &= ~cspinmask;
}

void ssd1306_xfer_stop(void){ 
}

//----------------------------------------
void i2c_sendByte(uint8_t byte){
  SPI.transfer(byte); 
}


void ssd1306_send_command(uint8_t command){
  *csport |= cspinmask;
  *dcport &= ~dcpinmask;
  *csport &= ~cspinmask;
  SPI.transfer(command);
}


void i2c_stop(void){
}

#define KEY_LEFT 1 
#define KEY_RIGHT 2
#define LEFT_BUTTON 1
#define RIGHT_BUTTON 2

int buttons()
{
  int a=0;
  if (digitalRead(PIN_LEFT_BUTTON)==0) return(KEY_LEFT);
  if (digitalRead(PIN_RIGHT_BUTTON)==0) return(KEY_RIGHT);
  if (digitalRead(PIN_B_BUTTON)==0) return(KEY_RIGHT);
  return(0);
}

void powerDown(int i)
{
}
