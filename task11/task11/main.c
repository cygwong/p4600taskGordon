/*
 * task11.c
 *
 * Created: 21-Nov-19 11:04:40 AM
 * Author : user
 */ 

#define F_CPU 10000000 
#include <avr/io.h>
#include <util/delay.h>

uint16_t getADC()
{
	uint16_t lowbyte;
	uint16_t highbyte;
	lowbyte = ADCL;
	
	ADCSRA |= (1<<ADSC);
	
	while(! ADCSRA && (1<<ADIF)); //loop until read complete
	highbyte = ADCH;
	
	uint16_t finalvalue;
	
	finalvalue = (highbyte << 8)| lowbyte;
	return finalvalue;
}
void turnoff()
{
	PORTD &= ~(1<<PD5);
	PORTD &= ~(1<<PD6);
	PORTD &= ~(1<<PD7);
}

void stoplight(uint16_t val)
{
	if (val <= 300) PORTD |= (1<<PD5);
	if (val >= 300 && val <=600) PORTD |= (1<<PD6);
	if (val > 600) PORTD |= (1<<PD7);
}


void loop()
{
	uint16_t valueget;
	valueget = getADC();
	stoplight(valueget);
	turnoff();
}

void setup()
{
	//set lights
	DDRD |= (1<<PD7);
	DDRD |= (1<<PD6);
	DDRD |= (1<<PD5);
	//start adc
	ADCSRA |= (1<<ADEN);
	//set adc
	ADMUX |= (1<<MUX2) | (1<<MUX0); // adc 5
	//set adc mode
	ADMUX |= (1<<REFS0);
	//program check
}

int main()
{
	setup();
	PORTD |= (1<<PD7);
	_delay_ms(100);
	turnoff();
	while(1) loop();
}


