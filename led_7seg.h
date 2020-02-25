/*
 * led_7seg.h
 *
 *  Created on: 20 sie 2015
 *      Author: wojtek
 */

#ifndef LED_7SEG_H_
#define LED_7SEG_H_

//definicje portow i pinow
#define LED_DATA PORTD					//segmenty dolaczone do portu D
#define LED_DATA_DIR DDRD				//kierunek portu
#define ANODY_PORT	PORTB				//anody podlaczone do portu B
#define ANODY_DIR	DDRB				// kierunek portu B

#define	CA0	(1<<PB0)					//anoda pierwszej cyfry sterowana z PB0
#define CA1 (1<<PB1)
#define CA2 (1<<PB2)
#define CA3 (1<<PB3)

#define SEG_A (1<<0)					//przyporzadkowanie numeru portu do segmentu
#define SEG_B (1<<1)
#define SEG_C (1<<2)
#define SEG_D (1<<3)
#define SEG_E (1<<4)
#define SEG_F (1<<5)
#define SEG_G (1<<6)

//extern - zmienne beda dostepne w kazdym pliku, ktory dolaczy ten plik naglowkowy, volatile - nie beda odkladane do rejestru
extern volatile uint8_t cy0;
extern volatile uint8_t cy1;
extern volatile uint8_t cy2;
extern volatile uint8_t cy3;
extern volatile uint8_t check_temp;
void d_led_init(void);

#endif /* LED_7SEG_H_ */
