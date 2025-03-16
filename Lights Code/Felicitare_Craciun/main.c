#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void display(char p, char c)
{
	PORTA = 0b11110000;
	PORTC = 0b00000000;
	
	switch(c)
	{
		case 0:
		PORTC |= 0b00111111; break;
		case 1:
		PORTC |= 0b00000110; break;
		case 2:
		PORTC |= 0b01011011; break;
		case 3:
		PORTC |= 0b01001111; break;
		case 4:
		PORTC |= 0b01100110; break;
		case 5:
		PORTC |= 0b01101101; break;
		case 6:
		PORTC |= 0b01111101; break;
		case 7:
		PORTC |= 0b00000111; break;
		case 8:
		PORTC |= 0b01111111; break;
		case 9:
		PORTC |= 0b01100111; break;
		case 'H':
		PORTC |= 0b01110110; break;
		case 'O':
		PORTC |= 0b00111111; break;
		case 'J':
		PORTC |= 0b00001110; break;
		case 'Y':
		PORTC |= 0b01101110; break;
	}
	
	switch(p)
	{
		case 1:
		PORTA |= 0b00000001; break;
		case 2:
		PORTA |= 0b00000010; break;
		case 3:
		PORTA |= 0b00000100; break;
		case 4:
		PORTA |= 0b00001000; break;
	}
}

void init_ADC()
{
	ADMUX |= 0b01000000;
	ADCSRA |= 0b10000111;
}

int adc_h, adc_l;

int readADC(int ch)
{
	ADMUX &= 0b11000000;
	ADMUX |= ch;
	ADCSRA |= (1<<6);
	while(ADCSRA & (1<<6));
	adc_l=ADCL;
	adc_h=ADCH;
	return (adc_h<<8)|(adc_l);
}


void init_pwm()
{
	TCCR0|=0b011101011;
	OCR0|=84;
	DDRB |= (1<<3);
}

void init_timer()
{
	TCCR2 |= 0b00001100;
	OCR2 =125;
	TIMSK |= 0b10000000;
}

int ms1=0, ms2=0, ms3=0, digit1=0, digit2=0, digit3=0;
int led_state=0, blink_count=0, phase=0, direction=0, led_index = 0;

int current_pattern = 0; 
int last_button_state = 0;

ISR(TIMER2_COMP_vect)
{
	int button_state = PINB & (1<<PB7);
	if(button_state && !last_button_state)
	{
		if(current_pattern >= 3)
		{
			current_pattern = 1;  
		} 
		else 
		{
			current_pattern++;    
		}
	}
	last_button_state = button_state;
	
	if(current_pattern == 1) 
	{
		ms1++;
		if (ms1 % readADC(6) == 0)
		{
			if(led_state==3)
			led_state++;
			if (led_state <= 6)
			{
				PORTD |= (1 << led_state);
				led_state++;
			}
			else
			{
				PORTD = 0b00000000;
				led_state = 0;
			}
		}
		digit1++;
		switch(digit1)
		{
			case 1: display(1, 'H' ); break;
			case 2: display(2, 'O'); break;
			case 3: display(3, 'H'); break;
			case 4: display(4, 'O'); digit1 = 0; break;
		}
	}
	 if(current_pattern == 2)  
	{
		ms2++;
		if (ms2 % readADC(6) == 0)
		{
			if (phase == 0)
			{
				PORTD ^= (1 << 0);
				PORTD ^= (1 << 2);
				PORTD ^= (1 << 5);
				blink_count++;
				if (blink_count >= 4)
				{
					blink_count = 0;
					phase = 1;
					PORTD = 0b00000000;
				}
			}
			else if (phase == 1)
			{
				PORTD ^= (1 << 1);
				PORTD ^= (1 << 4);
				PORTD ^= (1 << 6);
				blink_count++;
				if (blink_count >= 4)
				{
					blink_count = 0;
					phase = 0;
					PORTD = 0b00000000;
				}
			}
		}
		digit2++;
		switch(digit2)
		{
			case 2: display(2, 'J'); break;
			case 3: display(3, 'O'); break;
			case 4: display(4, 'Y'); digit2 = 0; break;
		}
	}
	 if(current_pattern == 3)  
	{
		ms3++;
		if (ms3 % readADC(6) == 0)
		{

			if (direction == 1)
			{
				PORTD |= (1 << led_index);
				led_index++;
				if(led_index==3)
				led_index++;
				if (led_index > 7)
				{
					led_index = 6;
					direction = 0;
				}
			}
			else
			{
				PORTD &= ~(1 << led_index);
				led_index--;
				if (led_index < 0)
				{
					led_index = 0;
					direction = 1;
					PORTD = 0b00000000;
				}
			}
		}
		digit3++;
		switch(digit3)
		{
			case 1: display(1, 2); break;
			case 2: display(2, 0); break;
			case 3: display(3, 2); break;
			case 4: display(4, 5); digit3 = 0; break;
		}
	}
}

int main(void)
{
	DDRD = 0b01111111;  
	PORTD = 0b10000000; 
	DDRB |= 0b00000111;
	init_pwm();
	init_timer();
	init_ADC();
	SREG |= (1<<7);
	while (1)
	{
	}
}