#include <avr/io.h> 
#include <stdint.h>

void play(uint16_t f, uint16_t t)
{
	for (uint16_t i=0; i<t;) 
   	{ 
    	if (TCNT1 >= f) 
      	{ 
         	PORTB ^= 1; // Toggle the LED 
         	TCNT1 = 0; // Reset timer value  
			i++;
      	} 
   	} 
	return;
}

int main (void) 
{ 
  	DDRB =1; // Set LED as output 

	TCCR1B |= (1 << CS10) | (1 << CS11); // Set up timer

	for(;;)
	{
	/*	play(1419, 220);
  		play(709, 220);
		play(354, 440);
		play(176, 1760);
		*/

		play(670, 662);
		play(670, 165);
		play(596, 185);
		play(531, 208);
		play(473, 234);
		play(670, 1324);
		play(752, 294);
		play(596, 278);
		play(563, 196);
		play(531, 208);
		play(563, 196);
		play(563, 196);
		play(473, 234);
		/*play(466, 1324);
		play(466, 331);
		play(523, 371);
		play(587, 417);
		play(659, 468);
		play(466, 1324);
		play(415, 294);
		play(523, 278);
		play(554, 196);
		play(587, 208);
		play(554, 196);
		play(554, 196);*/
	}
	return 0;
}

