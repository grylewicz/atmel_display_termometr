/*
 * main.c
 *
 *  Created on: 20 sie 2015
 *      Author: wojtek
 *      	  : v.1.3
 */
// Fusebity dla ATtiny2313: high: DF, low: 64

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "led_7seg.h"
#include "ds18b20.h"


int main(void)
{

	d_led_init();				//inicjalizacja wyswietlacza 7-seg

	//wyswietla wersje softu
	cy0 = 3;
	cy1 = 1;

	sei();						//wlaczenie globalnego zezwolenia na przerwania
	ds18b20_config();			//ustawia rodzielczosc 9-bitow
	_delay_ms(500);



	//petla glowna
	while(1)
	{

		if (check_temp > 200)						//pomiar co ~sekunde, check_temp zwiekszane w przerwaniu
		{
			if(ds18b20_reset())						// sprawdzam obecnosc ds18b20, jesli nie podlaczony, Err na LED
						{
							cy0 = 14;
							cy1 = 13;				//r
							cy2 = 13;				//r
							cy3 = 12;				//E
						}

					else

						{
							//odczyt temperatury z ds18b20
							uint8_t temp = ds18b20_read_temperature();

							uint8_t sign = (temp & 0x80) >> 7;		//sprawdzanie, czy temp ujemna
							if (sign)								//jesli ujemna
							{
								temp = ~temp;						//konwersja liczby ujemnej
								temp ++;							//na dodatnia
							}


							cy0 = 10;						 		//symbol stopien
							cy1 = temp%10;					 		//jednosci
							/* wariant 1, temp + i -, znak - na cy3, brak nieznaczacych '0'
							cy2 = (temp < 10 ? 14 : temp/10);		//dziesiatki lub pusto gdy temp<10
							cy3 = (sign == 0 ? 14 : 11);			//pusto lub '-' gdy temp < 0
							*/

							// wariant 2, - na cy2 gdy temp <10
							if (temp < 10)							//jesli mniejsza od 10
							{
								cy2 = (sign == 1 ? 11 : 14);		//i ujemna, to minus, jak dodatnia, to pusto
							}
							else
							{
								cy2 = temp/10;						//jesli > 10, to cyfra dzisiatek
							}
							cy3 = ((sign == 1 && temp>9) ? 11 : 14);//jestli ujemna i > 10 to '-', inaczej pusto

						}
			check_temp = 0;											//wyzeruj kontrolke odczytu z ds18b20
		}

	}
}
