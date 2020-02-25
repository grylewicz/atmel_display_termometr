/*
 * ds18b20.h
 *
 *  Created on: 20 sie 2015
 *      Author: wojtek
 */

#ifndef DS18B20_H_
#define DS18B20_H_

// Definiujemy pod jaki pin jest podpieta magistrala 1-wire
#define DS18B20_PORT PORTB
#define DS18B20_DDR DDRB
#define DS18B20_PIN PINB
#define DS18B20_DQ PB4

//Pin jako wejscie i wyjscie
#define DS18B20_INPUT_MODE DS18B20_DDR &= ~(1<<DS18B20_DQ)
#define DS18B20_OUTPUT_MODE DS18B20_DDR |= (1<<DS18B20_DQ)

//Ustawianie stanu wysokiego i nieskiego
#define DS18B20_LOW DS18B20_PORT &= ~(1<<DS18B20_DQ)
#define DS18B20_HIGH DS18B20_PORT |= (1<<DS18B20_DQ)

//Komendy dla DS18B20
#define DS18B20_CMD_SKIPROM 0xCC
#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xBE
#define DS18B20_CMD_WSCRATCHPAD 0x4E


//Deklaracje funkcji
uint8_t ds18b20_reset(void);
void ds18b20_write_bit(uint8_t bit);
uint8_t ds18b20_read_bit(void);
void ds18b20_write_byte (uint8_t byte);
uint8_t ds18b20_read_byte(void);
void ds18b20_config (void);
uint8_t ds18b20_read_temperature(void);


#endif /* DS18B20_H_ */
