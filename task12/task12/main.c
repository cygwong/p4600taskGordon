/*
 * task12.c
 *
 * Created: 25-Nov-19 10:56:05 AM
 * Author : user
 */ 

#include <avr/io.h>
#define F_CPU 10000000
#include <util/delay.h>

void setup()
{
	DDRB |= (1<<PB5);//clock as output
	DDRB |= (1<<PB3);//mosi as output
	DDRB |= (1<<PB6);//cs output as PB6
	DDRB |= (1<<PB2);//ss as output, needs to be pulled up
	//spi
	SPCR |= (1<<SPE); //spi enable
	//SPCR |= (1<<DORD);//data order
	SPCR |= (1<< MSTR);//set as master
	//SPCR |= (1<<CPOL);//polarty
	SPCR |= (1<<SPR0);//set clock freq
	SPCR |= (1<<SPR1);
	
	PORTB |=(1<<PB6);//mosi and sck as outputs
	PORTB |=(1<<PB5);
	_delay_ms(100);
}
void send(uint8_t num)
{
	uint8_t data = num;
	uint8_t datar;
	
	PORTB &= ~(1<<PB6);// pull chip select low
	
	SPDR = data;	
	
	while(!(SPSR & (1<<SPIF)));
	
	datar = SPDR;
	PORTB |=(1<<PB6);
	
	PORTB &= ~(1<<PB6);// pull chip select low
}
void loop()
{
	uint8_t dat = 0;
	for (dat=0; dat<128; dat++)
	{
		send(dat);
		_delay_ms(100);
	}
}
int main(void)
{
	setup();
    while (1) loop();
}

