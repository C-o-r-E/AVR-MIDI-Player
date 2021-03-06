/*
	for the atmega88PA
*/
#include <avr/io.h> 
#include <stdint.h>

void play(uint16_t f, uint16_t t)
{
	uint8_t toggle = 1;
	if(!f)
	{
		toggle = 0;
		f = 709;	
	}
	for (uint16_t i=0; i<t;) 
   	{ 
    	if (TCNT1 >= f) 
      	{ 
         	PORTB ^= toggle; // Toggle the LED 
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

		// LOVE COLORED MASTER SPARK //
		play(596, 743);
		play(596, 185);
		play(446, 248);
		play(397, 278);
		play(375, 295);
		play(596, 743);
		play(596, 185);
		play(446, 310);
		play(397, 278);
		play(0, 78);
		play(375, 295);
		play(596, 743);
		play(596, 185);
		play(446, 248);
		play(397, 278);
		play(375, 295);
		play(596, 743);
		play(596, 185);
		play(446, 310);
		play(397, 278);
		play(0, 78);
		play(375, 295);
		play(596, 92);
		play(501, 110);
		play(446, 124);
		play(0, 78);
		play(596, 92);
		play(501, 110);
		play(446, 124);
		play(0, 78);
		play(596, 92);
		play(501, 110);
		play(446, 124);
		play(596, 92);
		play(0, 78);
		play(375, 110);
		play(0, 39);
		play(397, 69);
		play(375, 73);
		play(397, 139);
		play(446, 124);
		play(501, 110);
		play(669, 82);
		play(596, 92);
		play(501, 110);
		play(0, 78);
		play(669, 82);
		play(596, 92);
		play(501, 110);
		play(0, 78);
		play(596, 92);
		play(501, 110);
		play(446, 124);
		play(596, 92);
		play(0, 78);
		play(297, 139);
		play(0, 39);
		play(334, 82);
		play(297, 92);
		play(334, 165);
		play(375, 147);
		play(397, 139);
		play(596, 92);
		play(501, 110);
		play(446, 124);
		play(0, 78);
		play(596, 92);
		play(501, 110);
		play(446, 124);
		play(0, 78);
		play(596, 92);
		play(501, 110);
		play(446, 124);
		play(596, 92);
		play(0, 78);
		play(375, 110);
		play(0, 39);
		play(397, 69);
		play(375, 73);
		play(397, 139);
		play(446, 124);
		play(501, 110);
		play(669, 82);
		play(596, 92);
		play(751, 73);
		play(0, 78);
		play(796, 69);
		play(0, 78);
		play(1003, 55);
		play(0, 78);
		play(893, 62);
		play(1193, 46);
		play(796, 69);
		play(1193, 46);
		play(0, 78);
		play(751, 92);
		play(0, 58);
		play(751, 73);
		play(669, 82);
		play(596, 557);
		play(669, 82);
		play(501, 110);
		play(446, 620);
		play(596, 92);
		play(397, 139);
		play(375, 147);
		play(397, 556);
		play(501, 221);
		play(446, 248);
		play(596, 464);
		play(0, 78);
		play(596, 92);
		play(501, 110);
		play(446, 744);
		play(596, 92);
		play(501, 110);
		play(446, 620);
		play(596, 92);
		play(397, 139);
		play(375, 147);
		play(397, 556);
		play(375, 295);
		play(334, 331);
		play(297, 743);
		play(297, 185);
		play(334, 165);
		play(375, 147);
		play(397, 139);
		play(421, 131);
		play(375, 147);
		play(562, 98);
		play(0, 78);
		play(375, 147);
		play(421, 131);
		play(751, 73);
		play(421, 788);
		play(562, 98);
		play(421, 131);
		play(562, 98);
		play(421, 131);
		play(375, 147);
		play(562, 98);
		play(0, 78);
		play(375, 147);
		play(421, 131);
		play(751, 73);
		play(421, 788);
		play(375, 147);
		play(354, 156);
		play(375, 147);
		play(421, 131);
		play(375, 147);
		play(562, 98);
		play(0, 78);
		play(375, 147);
		play(421, 131);
		play(751, 73);
		play(280, 393);
		play(375, 147);
		play(354, 156);
		play(375, 147);
		play(421, 131);
		play(473, 117);
		play(562, 98);
		play(473, 117);
		play(421, 131);
		play(375, 147);
		play(562, 98);
		play(0, 78);
		play(375, 147);
		play(421, 131);
		play(751, 73);
		play(421, 788);
		play(562, 98);
		play(421, 131);
		play(562, 98);
		play(421, 131);
		play(375, 147);
		play(562, 98);
		play(0, 78);
		play(375, 147);
		play(421, 131);
		play(751, 73);
		play(421, 788);
		play(375, 147);
		play(354, 156);
		play(375, 147);
		play(421, 131);
		play(375, 147);
		play(562, 98);
		play(0, 78);
		play(375, 147);
		play(421, 131);
		play(751, 73);
		play(280, 393);
		play(375, 147);
		play(354, 156);
		play(375, 147);
		play(421, 131);
		play(473, 117);
		play(562, 98);
		play(473, 117);
		play(421, 131);
		play(375, 147);
		play(562, 98);
		play(0, 78);
		play(375, 147);
		play(421, 131);
		play(751, 73);
		play(421, 1182);
		play(562, 787);
		play(562, 196);
		play(421, 262);
		play(375, 295);
		play(354, 312);
		play(562, 787);
		play(562, 196);
		play(421, 328);
		play(375, 295);
		play(0, 78);
		play(354, 312);
		play(562, 787);
		play(562, 196);
		play(421, 262);
		play(375, 295);
		play(354, 312);
		play(562, 787);
		play(562, 196);
		play(421, 328);
		play(375, 295);
		play(0, 78);
		play(354, 312);
		play(562, 787);
		play(562, 196);
		play(421, 262);
		play(375, 295);
		play(354, 312);
		play(562, 787);
		play(562, 196);
		play(421, 328);
		play(375, 295);
		play(0, 78);
		play(354, 312);
		play(562, 787);
		play(562, 196);
		play(421, 262);
		play(375, 295);
		play(354, 312);
		play(562, 787);
		play(562, 196);
		play(421, 328);
		play(375, 295);
		play(0, 78);
		play(354, 312);
		play(0, 1250);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(397, 835);
		play(531, 104);
		play(397, 139);
		play(531, 104);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(397, 835);
		play(354, 156);
		play(334, 165);
		play(354, 156);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(265, 417);
		play(354, 156);
		play(334, 165);
		play(354, 156);
		play(397, 139);
		play(446, 124);
		play(531, 104);
		play(446, 124);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(397, 835);
		play(531, 104);
		play(397, 139);
		play(531, 104);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(397, 835);
		play(354, 156);
		play(334, 165);
		play(354, 156);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(265, 417);
		play(354, 156);
		play(334, 165);
		play(354, 156);
		play(397, 139);
		play(446, 124);
		play(531, 104);
		play(446, 124);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(397, 835);
		play(531, 104);
		play(397, 139);
		play(531, 104);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(397, 835);
		play(354, 156);
		play(334, 165);
		play(354, 156);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(265, 417);
		play(354, 156);
		play(334, 165);
		play(354, 156);
		play(397, 139);
		play(446, 124);
		play(531, 104);
		play(446, 124);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(397, 835);
		play(531, 104);
		play(397, 139);
		play(531, 104);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(397, 835);
		play(354, 156);
		play(334, 165);
		play(354, 156);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(265, 417);
		play(354, 156);
		play(334, 165);
		play(354, 156);
		play(397, 139);
		play(446, 124);
		play(531, 104);
		play(446, 124);
		play(397, 139);
		play(354, 156);
		play(531, 104);
		play(0, 78);
		play(354, 156);
		play(397, 139);
		play(709, 78);
		play(397, 1253);


	}
	return 0;
}

