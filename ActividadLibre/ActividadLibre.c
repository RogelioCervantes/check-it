#include <avr/io.h>
#include <util/delay.h>

void game();
void display(int i);
void check();
void win();

int points = 0;
int delay = 250;
int difficulty = 25;
int display_g = 0;

int main(void)
{
	DDRD = 0xFF;	//Leds
	DDRB = 0x00; 	//Button
	DDRC = 0xFF; 	//Display
	display(0);

	while (1)
	{
		game();
	}
}

void game() // Secuencia de movimiento de los leds
{	check();
	if (display_g == 1) PORTD = 0x81;
	else PORTD = 0x01;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0x82;
	else PORTD = 0x02;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0x84;
	else PORTD = 0x04;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0x88;
	else PORTD = 0x08;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0x90;
	else PORTD = 0x10;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0xA0;
	else PORTD = 0x20;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0xC0;
	else PORTD = 0x40;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0xA0;
	else PORTD = 0x20;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0x90;
	else PORTD = 0x10;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0x88;
	else PORTD = 0x08;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0x84;
	else PORTD = 0x04;
	_delay_ms(delay);
	check();
	if (display_g == 1) PORTD = 0x82;
	else PORTD = 0x02;
	_delay_ms(delay);
	check();
}

void display(int i) // Números del display (puntaje)
{
	switch(i)
		{
		case 0: PORTC = 0x3F;
				break;
		case 1: PORTC = 0x06;
				display_g = 0;
				break;
		case 2: PORTC = 0x1B;
				display_g = 1;
				break;
		case 3: PORTC = 0x0F;
				break;
		case 4: PORTC = 0x26;
				break;
		case 5: PORTC = 0x2D;
				break;
		case 6: PORTC = 0x3D;
				display_g = 1;
				break;
		case 7: PORTC = 0x07;
				display_g = 0;
				break;
		case 8: PORTC = 0x3F;
				display_g = 1;
				break;
		case 9: PORTC = 0x2F;
				break;
		default: PORTC = 0x00;
	}
}

void check() // Comprueba si se presionó el botón en el momento correcto
{	
	if (PINB == 0x01)
	{
		DDRB &= ~(1 << 0);
		if (PORTD == 0x08 || PORTD == 0x88)
		{
			points += 1;			
			display(points);
			if (points == 10) win();
			delay -= difficulty;
			for (int i = 0; i <= 5; i++)
			{
				if (display_g == 1) PORTD = 0x80;
				else PORTD = 0x00;
				_delay_ms(75);
				if (display_g == 1) PORTD = 0x88;
				else PORTD = 0x08;
				_delay_ms(75);
			}
			_delay_ms(250);
			_delay_ms(250);
			if (display_g == 1) PORTD = 0x80;
			else PORTD = 0x00;
			_delay_ms(250);
			_delay_ms(250);
		} 
		else 
		{
			if (points != 0) points -= 1;
			if (delay != 250) delay += 25;
			display(points);
			for (int i = 0; i <= 3; i++)
			{
				if (display_g == 1) PORTD = 0x80;
				else PORTD = 0x00;
				_delay_ms(150);
				if (display_g == 1) PORTD = 0xFF;
				else PORTD = 0x7F;
				_delay_ms(150);
			}
			_delay_ms(250);
			_delay_ms(250);
			if (display_g == 1) PORTD = 0x80;
			else PORTD = 0x00;
			_delay_ms(250);
			_delay_ms(250);
		}
		DDRB |= (1 << 0);
	}
}

void win() // Esto se ejecuta cuando se llega al máximo de puntos (cuando ganas)
{
	while (1)
	{
		PORTD = 0x41;
		PORTC = 0xFF;
		_delay_ms(75);
		PORTD = 0x22;
		PORTC = 0x00;
		_delay_ms(75);
		PORTD = 0x14;
		PORTC = 0xFF;
		_delay_ms(75);
		PORTD = 0x08;
		PORTC = 0x00;
		_delay_ms(75);
		PORTD = 0x14;
		PORTC = 0xFF;
		_delay_ms(75);
		PORTD = 0x22;
		PORTC = 0x00;
	}
}
