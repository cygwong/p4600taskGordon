/*
 * task8.c
 *
 * Created: 07-Nov-19 10:11:45 AM
 * Author : Gordon
 */ 
#define F_CPU 10000000  
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t keep_going = 1;

void loop()
{
	//toggle the LED on and off
	PORTD |= (1<<PD1);//turns
	_delay_ms(100);
	
	PORTD &= ~(1<<PD1);//turns off
	_delay_ms(100);
}

void setup()
{
	DDRD |= (1<<PD1);
}

int main()
{
	setup();
	while(keep_going) loop();
	
	return 0;
}

