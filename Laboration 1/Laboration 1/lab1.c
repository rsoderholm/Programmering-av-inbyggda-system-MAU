/*
 * lab1.c
 *
 * Created: 2016-11-01 14:42:40
 *  Author: staff
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include "numkey/numkey.h"
#include "delay/delay.h"
#include "lcd/lcd.h"

int main(void)
{

	numkey_init();
	lcd_init();
	lcd_clear();
	
	while(1)
	{
		char input = numkey_read();
		
		if (input != 0)
		{
			if(input == 'D')
			{
				lcd_clear();
			} else
				lcd_write(CHR, input);
		}
		
		while(input != 0)
		{
			input = numkey_read();
		}
	

	}
}