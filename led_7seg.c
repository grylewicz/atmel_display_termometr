/*
 * led_7seg.c
 *
 *  Created on: 20 sie 2015
 *      Author: wojtek
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "led_7seg.h"

volatile uint8_t cy0;												//bufory cyfr
volatile uint8_t cy1;
volatile uint8_t cy2;
volatile uint8_t cy3;
volatile uint8_t check_temp;										//do opoznienia odczytu temperatury

const uint8_t cyfry[15] PROGMEM = {
		~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F),			//0
		~(SEG_B | SEG_C),											//1
		~(SEG_A | SEG_B | SEG_D | SEG_E | SEG_G),					//2
		~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_G),					//3
		~(SEG_B | SEG_C | SEG_F | SEG_G),							//4
		~(SEG_A | SEG_C | SEG_D | SEG_F | SEG_G),					//5
		~(SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G),			//6
		~(SEG_A | SEG_B | SEG_C | SEG_F),							//7
		~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G),	//8
		~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G),			//9
		~(SEG_A | SEG_B | SEG_F | SEG_G),							//stopien
		~(SEG_G),													//-
		~(SEG_A | SEG_D | SEG_E | SEG_F | SEG_G),					//E
		~(SEG_E | SEG_G),											//r
		0xFF														//pusty
};

void d_led_init(void)
{
	LED_DATA_DIR = 0xFF;											//wszystkie porty jako wyjscia - sterowanie katodami
	LED_DATA = 0xFF;												//wygaszenie wszystkich katod
	/* 4 piny portu B jako wyjscia (sterowanie anodami wyswietlaczy) */
	ANODY_DIR |= CA0 | CA1 | CA2 | CA3;
	/* wygaszenie wszystkich wyswietlaczy */
	ANODY_PORT &= 0xF0;

	// ustawienie TIMER0
	TCCR0A |= (1<<WGM01);											//tryb CTC
	TCCR0B |= (1<<CS01) | (1<<CS00); 								//preskaler 64
	OCR0A = 77; 													//dodatkowy podział‚ przez 77, dający przerwanie co ~200Hz
	TIMSK |= (1<<OCIE0A); 											//zezwolenie na przerwanie Compare Match
}


// =================== PROCEDURA OBSŁUGI PRZERWANIA ==============================
ISR (TIMER0_COMPA_vect)
{
	static uint8_t licznik = 1; 						//zmienna do przelaczania kolejno anod wyswietlaczy
	ANODY_PORT &= 0xF0;									//wygasza cyfry, zeby nie bylo podswietlania segmentow
	if(licznik == 1) LED_DATA = pgm_read_byte( &cyfry[cy0] );	//na port wystaw dane zapalajace segmenty
	else if (licznik == 2) LED_DATA = pgm_read_byte( &cyfry[cy1] );
	else if (licznik == 4) LED_DATA = pgm_read_byte( &cyfry[cy2] );
	else if (licznik == 8) LED_DATA = pgm_read_byte( &cyfry[cy3] );

	//cykliczne przelaczanie w kazdym przerwaniu, podanie zasilania na anodę 0001-0010-0100-1000
	ANODY_PORT = (ANODY_PORT & 0xF0) | (licznik & 0x0F);			//licznik na port anod

	licznik <<= 1;										//przesun zawartosc licznika o 1 w lewo i wpisz w licznik
	if(licznik>8) licznik = 1;
	check_temp++;										//zwiększ o 1 wartość check_temp
}
