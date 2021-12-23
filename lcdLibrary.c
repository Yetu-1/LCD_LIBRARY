/* library  for a 16*2 LCD */
/* LCD library by SALIHU DAVID YETU  22/03/2020 , feel free to edit the library for your projects.
   For more information on the device download and read the hITACHI HD447880U DATASHEET*/

#include "lcdLibrary.h"
#include <util/delay.h>
uint8_t interface = 0;

//Clear Display
/*write "20H" to DDRA and set DDRAM address to "00H" from AC*/
void lcdClear(){
	PORTB &= ~(1 << RS);
	PORTB &= ~(1 << RW);
	if(interface == 4){
		write4bit(0b00000001);
	}
	else{
		write8bit(0b00000001);
	}
	_delay_us(2000);
}

//Return Home
/*set DDRAM address  to "00H" from ac and return cursor to its 
  original position if shifted. The contents of DDRAM are not changed
 */
void returnHome(){
		PORTB &= ~(1 << RS);
		PORTB &= ~(1 << RW);
		if(interface == 4){
			write4bit(0b00000010);
		}
		else{
			write8bit(0b00000010);
		}
		_delay_us(2000);
}

/* shift all the display to the right, cursor moves according to the display*/
void scrollDisplayRight(){
		PORTB &= ~(1 << RS);
		PORTB &= ~(1 << RW);
			if(interface == 4){
				write4bit(0b00011100);
			}
			else{
				write8bit(0b00011100);
			}
		_delay_us(20);
}

/*shift all the display to the left, cursor moves according to the display*/ 
void scrollDisplayLeft(){
		PORTB &= ~(1 << RS);
		PORTB &= ~(1 << RW);
       	if(interface == 4){
	       	write4bit(0b00011000);
       	}
       	else{
	       	write8bit(0b00011000);
       	}
		_delay_us(20);
}

/*set cursor to specified address in the DDRAM */
void setCursor(uint8_t row, uint8_t column){
	if (row == 1){}
	else{
		column += (0x40);
	}
		PORTB &= ~(1 << RS);
		PORTB &= ~(1 << RW);
		if(interface == 4){
			write4bit((column-1) | (1 << PORTD7));
		}
		else{
			write8bit((column-1) | (1 << PORTD7));
		}
		_delay_us(20);
}

// initialize LCD
void initlcd(uint8_t mode){
	if(mode == 4){
		init4bit();
		interface = 4;
	}
	else{
		init8bit();
		interface = 8;
	}
	lcdClear();
}


/* function takes in a string and prints it out on the LCD */
void lcdPrint(char myString[]){
	  uint8_t i = 0;
	  while (myString[i]) {
		PORTB |= (1 << RS);
		PORTB &= ~(1 << RW);
		if(interface == 4){
			write4bit(myString[i]);
		}
		else{
			write8bit(myString[i]);
		}
		i++;
	  }
}

/* controls the enable bit while accepting data from the data pins */
void pulseEnable(){
	PORTB &= ~(1 << enable);
	_delay_us(2);
	PORTB  |= (1 << enable);
	_delay_us(2);    // enable pulse must be >450ns
	PORTB &= ~(1 << enable);
	_delay_us(100);   // commands need > 37us to settle
}

/* printing out a character in 8-bit mode of the LCD */
void write8bit(char character){
	PORTD = character;
	pulseEnable();
}

/* printing out a character in 4-bit mode of the LCD */
void write4bit(char character){
	PORTD = (character);
	pulseEnable();
	PORTD = (character << 4);
	pulseEnable();
}
void init4bit(void){
	    /*initialize LCD and set to 4-bit bus mode with MPU 
        set to 2-line display mode and set to 5x8 dots format display mode*/ 
	    _delay_ms(50);
		PORTB &= ~(1 << RS);
	    PORTB &= ~(1 << RW);
		write4bit(0b00110000);  // three attmepts according to the datasheet
		_delay_us(4500);
		write4bit(0b00110000);
		_delay_us(100);
		write4bit(0b00110000);
		_delay_us(100);
		write4bit(0b00101000);
		_delay_us(100);
		
		//display on/off control
	    /* sets the display on or off , on/off cursor and Blinking of cursor*/
		PORTB &= ~(1 << RS);
		PORTB &= ~(1 << RW);
		write4bit(0b00001111);
		pulseEnable();
}
void init8bit(void){
     	/*initialize LCD and set to 8-bit bus mode with MPU 
        set to 2-line display mode and set to 5x8 dots format display mode*/ 
		_delay_ms(50);
		PORTB &= ~(1 << RS);
		PORTB &= ~(1 << RW);
		PORTD = 0b00111000;
		pulseEnable();
		_delay_us(100);
		//display on/off control
        /* sets the display on or off , on/off cursor and Blinking of cursor*/
		PORTB &= ~(1 << RS);
		PORTB &= ~(1 << RW);
		PORTD = 0b00001111;
		pulseEnable();
}