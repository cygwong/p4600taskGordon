
#define F_CPU 10000000 UL
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_OVF_vect)
{
	PORTD ^= (1<<PD1);
}
ISR(TIMER0_COMPA_vect)
{
	PORTD ^= (1<<PD1);
}
void loop()
{
	
}

void setup()
{
	DDRD |= (1<<PD1);
	PORTD &= ~(1<<PD1);

	TCCR0B = 0X01;
	TIMSK0 = 1;
	TIMSK0 |= (1<<OCIE0A);//change bit to 1
	OCR0A = 50; //number to compare 

	sei();
}

int main()
{
	setup();
	while(1) loop();
}
