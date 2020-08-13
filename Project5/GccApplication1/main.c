/*
 * GccApplication1.c
 *
 * Created: 3/28/2017 3:05:09 PM
 * Author : oldham
 */ 

//PC0 Input 1 A-
//PC1 Input 2 A+
//PC2 Input 3 B-
//PC3 Input 4 B+
//PC4 Enable A
//PC5 Enable B

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 10000000UL
#include <util/delay.h>      // for _delay_ms()


volatile uint8_t stepnumber = 0;
volatile uint8_t steps = 0;

typedef enum {STATE_READY_FOR_PRESS, STATE_WAITING_FOR_RELEASE, STATE_DEBOUNCING_PRESS, STATE_DEBOUNCING_RELEASE} state_t1;

ISR(TIMER1_COMPA_vect, ISR_BLOCK){
	TCCR0B = 0;
	OCR1A += 11718;
	
	
	switch (stepnumber) {
		case 1 : {
			PORTC = 0b00000010;
			break;
		}
		case 2 : {
			PORTC = 0b00001000;
			break;
		}
		case 3 : {
			PORTC = 0b00000001;
			break;
		}
		case 4 : {
			PORTC = 0b00000100;
			stepnumber = 0;
			break;
		}
	}
	
	if (steps == 200) {
		// play buzzer
		TCCR0B |= (1 << CS01) | (1 << CS00);
		steps = 0;
	}
	
	stepnumber++;
	steps++;
}

uint8_t button_pressed() {
	return !(PIND & 0x01);
}

int main(void)
{
	DDRC = 0x0F;            // initialize port C to outputs
	//PORTC = 0b00000100;
	// motors connected across PC0...Pc3
	
	uint8_t running = 0;
	
	PORTD |= (1 << PD0); // enable pull up resistor
	DDRD &= ~(1 << PD0); // set button as input
	state_t1 button_state = STATE_READY_FOR_PRESS;
	
	TIMSK1 |= 0x02;
	sei();
	OCR1A = 11718;
	//TCCR1B |= (1 << CS12); // prescaler 256. each second is 39062 counts
	// 200 steps / minute
	
	// initalization of the timer that generates a 1kHz square wave for the buzzer
	// desired frequency is 1kHz. therefore, using a prescaler of 64, OCR0A must be set to 155
	// timer 0 is set to CTC mode, and to toggle on compare match
	DDRD |= (1 << PD6); // set OC0A pin as output
	TCCR0A |= (1 << WGM01) | (1 << COM0A0);
	OCR0A = 155;
		
	while(1) {
		switch (button_state) {
			case STATE_READY_FOR_PRESS : {
				if (button_pressed()) {
					button_state = STATE_DEBOUNCING_PRESS;
				}
				break;
			}

			case STATE_DEBOUNCING_PRESS : {
				_delay_ms(50);
				button_state = STATE_WAITING_FOR_RELEASE;
				if (running == 0) {
					TCCR1B |= (1 << CS12);
					steps = 1;
					running = 1;
				} else if (running == 1) {
					//stepnumber = 0;
					steps++;
					PORTC = 0;
					TCCR1B &= ~(1 << CS12);
					TCNT1 = 0;
					OCR1A = 11718;
					running = 0;
				}
				break;
				
			}

			case STATE_WAITING_FOR_RELEASE : {
				if (!button_pressed()) {
					button_state = STATE_DEBOUNCING_RELEASE;
				}
				break;
			}

			case STATE_DEBOUNCING_RELEASE : {
				_delay_ms(50);
				button_state = STATE_READY_FOR_PRESS;
				break;
			}
			

		}
		
		
	}
}


