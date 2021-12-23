/*
 * GccApplication11.c
 *
 * Created: 3/27/2020 4:39:11 AM
 * Author : User
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "i2c.h"

void write(uint8_t x);
void initialize(void);
void print(uint8_t x);
void set(uint8_t row, uint8_t column);

int main(void)
{
	
    initI2C();
	_delay_ms(250);
	
	i2cStart();
	i2cSend(0b01001110);
	i2cStop();
	initialize();
	set(2, 3);
    while (1) 
    {
    }
	return 0;
}

void write(uint8_t x){
// send most significant 4 bits
	i2cStart();
	i2cSend(0b01001110);
	i2cSend(((x >> 4) << 4));
	_delay_us(2);
	i2cSend(((x >> 4) << 4) | (1 << 2));
	_delay_us(2);
	i2cSend(((x >> 4) << 4) & ~(1 << 2));
	_delay_us(100);
	
// send least significant 4 bits
	i2cStart();
	i2cSend(0b01001110);
	i2cSend((x << 4));
	_delay_us(2);
	i2cSend((x << 4) | (1 << 2));
	_delay_us(2);
	i2cSend((x << 4) & ~(1 << 2));
	_delay_us(100);
	i2cStop();
}
void initialize(){
	    _delay_ms(50);
	    write(0b00110000);  // three attmepts according to the datasheet
	    _delay_us(4500);
	    write(0b00110000);
	    _delay_us(100);
	    write(0b00110000);
	    _delay_us(100);
	    write(0b00101000);
	    _delay_us(100);
		
		//display on/off control
		/* sets the display on or off , on/off cursor and Blinking of cursor*/
		write(0b00001111);		
}
void print(uint8_t x){
	// send most significant 4 bits
	i2cStart();
	i2cSend(0b01001110);
	i2cSend(((x >> 4) << 4) | ( 1));
	_delay_us(2);
	i2cSend(((x >> 4) << 4) | (1 << 2) | ( 1));
	_delay_us(2);
	i2cSend((((x >> 4) << 4) & ~(1 << 2)) | ( 1));
	_delay_us(100);
	
	// send least significant 4 bits
	i2cStart();
	i2cSend(0b01001110);
	i2cSend((x << 4)| ( 1));
	_delay_us(2);
	i2cSend((x << 4) | (1 << 2)| ( 1));
	_delay_us(2);
	i2cSend(((x << 4) & ~(1 << 2) )| ( 1));
	_delay_us(100);
	i2cStop();
}
void set(uint8_t row, uint8_t column){
	if (row == 1){}
	else{
		column += (0x40);
	}
	write((column-1) | (1 << PORTD7));
	_delay_us(20);
}
