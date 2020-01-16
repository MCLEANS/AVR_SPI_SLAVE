/*
 * AVR_SPI_SLAVE.cpp
 *
 * Created: 1/16/2020 1:18:40 PM
 * Author : MCLEANS
 */ 

/* The sample code below blinks an LED on pin PC0
	and services the SPI when data is available in the bus
*/
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define MISO_PORT_DIRECTION DDRB
#define MISO_PIN PINB4




//SPI transfer complete Interrupt Service Routine
ISR(SPI_STC_vect){

		PORTD = SPDR;
}

void spi_init_slave_mode(){
	//set MISO pin to output
	//the rest are left to inputs by default
	MISO_PORT_DIRECTION |= (1<<MISO_PIN);
	//enable the SPI and SPI interrupt
	SPCR |= (1<<SPE)|(1<<SPIE);
	//enable global interrupt
	sei();
}

int main(void)
{
	spi_init_slave_mode();
	DDRC |= (1<<PINC0);
	DDRD = 0b11111111;
	
	 while (1) {
		 PORTC ^= (1<<PINC0);
		_delay_ms(1000);
	 }
}

