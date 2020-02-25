/*
 * ds18b20.c
 *
 *  Created on: 20 sie 2015
 *      Author: wojtek
 */


#include <avr/io.h>
#include <util/delay.h>
#include "ds18b20.h"



//Reset magistrali i odpowiedz ukladu 1-wire
uint8_t ds18b20_reset(void)
{
	uint8_t i;
	//ustawianie 0 linii 1-wire
	DS18B20_LOW;
	DS18B20_OUTPUT_MODE;
	_delay_us(480);
	//oczekiwanie na odpowiedz z ds18b20
	DS18B20_INPUT_MODE;
	_delay_us(60);
	//sprawdzanie czy ds18b20 odpowiedzial (ustawil 0)
	i = (DS18B20_PIN & (1<<DS18B20_DQ));
	_delay_us(420);

	// zwracamy wynik resetu 1 - blad, ds18b20 nie odpowiedzial, 0 - OK
	return i;
}


//zapis bitu na magistrale
void ds18b20_write_bit(uint8_t bit)
{
	DS18B20_LOW;
	DS18B20_OUTPUT_MODE;
	_delay_us(1);

	if (bit) DS18B20_INPUT_MODE;

	_delay_us(60);
	DS18B20_INPUT_MODE;
}

//odczyt bitu z magistrali
uint8_t ds18b20_read_bit(void)
{
	uint8_t bit = 0;

	DS18B20_LOW;
	DS18B20_OUTPUT_MODE;
	_delay_us(1);

	DS18B20_INPUT_MODE;
	_delay_us(14);

	if (DS18B20_PIN & (1<<DS18B20_DQ)) bit=1;

	_delay_us(45);
	return bit;
}

//zapis bajtu na magistralę
void ds18b20_write_byte (uint8_t byte)
{
	uint8_t i=8;

	while(i--)
	{
		ds18b20_write_bit(byte&1);
		byte>>=1;
	}
}

//odczyt bajtu z magistrali
uint8_t ds18b20_read_byte(void)
{
	uint8_t i=8, n=0;

	while(i--)
	{
		//przesunięcie w prawo o jedną pozycję i zapisanie odczytanej wartości
		n>>=1;
		n |= (ds18b20_read_bit()<<7);
	}

	return n;
}


// ustawienie rozdzielczosci 9-bitowej
void ds18b20_config (void)
{
	ds18b20_reset();
	ds18b20_write_byte(DS18B20_CMD_SKIPROM);
	ds18b20_write_byte(DS18B20_CMD_WSCRATCHPAD);

	ds18b20_write_byte(0);					//zapis do TH Register
	ds18b20_write_byte(0);					//zapis do TL Register
	ds18b20_write_byte(0x1F);				//zapis do conf. register rozdzielczosci 9 bit
}


//odczyt temperatury
uint8_t ds18b20_read_temperature(void)
{
	uint8_t temperature[2];
	uint8_t digit;

	ds18b20_reset();
	ds18b20_write_byte(DS18B20_CMD_SKIPROM);
	ds18b20_write_byte(DS18B20_CMD_CONVERTTEMP);

	while(!ds18b20_read_bit());
	//Reset, pominięcie odczytu adresu, komenda odczytu Sratchpada
	ds18b20_reset();
	ds18b20_write_byte(DS18B20_CMD_SKIPROM);
	ds18b20_write_byte(DS18B20_CMD_RSCRATCHPAD);

	//Odczyt dwóch bajtów scratchpada i zapis do tablicy temperature
	temperature[0] = ds18b20_read_byte();			// mlodsze bity LSB
	temperature[1] = ds18b20_read_byte();			// starsze bity MSB
	ds18b20_reset();

	digit = temperature[0]>>4;						//pozbywam sie czesci ulamkowych
	digit |= (temperature[1]&0xF)<<4;				//przesuwam wartosc w lewo o 4 pozycje, sumuje z mlodszym bajtem, mam znak na najstarszym bicie
	//digit = (temperature[0]&0xF);
	return digit;									//zwracam temperaturę w liczbie całkowitej, znak na najstarszym bicie
}
