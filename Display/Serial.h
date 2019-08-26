/*
 * Serial.h
 *
 * Created: 23.08.2018 19:53:12
 *  Author: gerha
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_
#include <stdio.h>
// UART ist die Abkürzung für Universal Asynchronous Receiver Transmitter.

void uart_putchar(char c, FILE *stream);
char uart_getchar(FILE *stream);

void uart_init(void);
void Serial_begin(void);




#endif /* SERIAL_H_ */