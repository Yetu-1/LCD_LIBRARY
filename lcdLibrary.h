/* LCD library by SALIHU DAVID YETU  22/03/2020.
   For more information on the device download and read the hITACHI HD447880U DATASHEET*/

#include <avr/io.h>

#define RS PORTB4
#define RW PORTB2
#define enable PORTB3


//clear LCD 
void lcdClear(void);

//print string
void lcdPrint(char myString[]);

//initialize LCD
void initlcd(uint8_t mode);

//set and clear enable pin
void pulseEnable(void);

//return current DDRAM address to 00H
void returnHome(void);

// scroll display to the right
void scrollDisplayRight(void);

// scroll display to the left
void scrollDisplayLeft(void);

// set cursor position
void setCursor(uint8_t row, uint8_t column);

// print character on screen in 8 or 4 bit mode
void write8bit(char character);
void write4bit(char character);

// initializes 4 or 8 bit interface with the MPU
void init4bit();
void init8bit();