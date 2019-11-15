#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t keep_going = 1;

void loop()
{
    //toggle the LED on and off
    PORTD |= (1<<PD1);//turns 
    _delay_ms(1000);
    
    PORTD &= ~(1<<PD1);//turns off
   _delay_ms(1000);
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