/*
 * task10.c
 *
 * Created: 18-Nov-19 10:34:34 AM
 * Author : user
 */ 


#define F_CPU 10000000 UL
#include <avr/io.h>
#include <avr/interrupt.h>



void loop()
{
	
}

void setup()
{
	DDRD |= (1<<PD6);
	DDRD |= (1<<PD5);

	TCCR0A |= (1<<COM0A0) | (1<<COM0A1);
	TCCR0A |= (1<<COM0B0) | (1<<COM0B1);
	
	TCCR0A |= /*(1<<WGM01) |*/ (1<<WGM00);
	//TCCR0A &= ~(1<<WGM00);
	TCCR0B |=/* (1<<WGM02) |*/ (1<<CS00);
	//TCCR0B = 0X01; mode 7 was right

	OCR0A = 50; //number to compare
	//change duty cycle to change voltage and brightness
	OCR0B = 150;

}

int main()
{
	setup();
	while(1) loop();
}
