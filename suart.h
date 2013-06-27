/*
 * suart.h
 * Software UART header file, interface for elm-chan's SUART asm code.
 */

#ifndef SUART_H
#define SUART_H

void suart_init(void);
void suart_xmit(uint8_t);
uint8_t suart_rcvr(void);

#endif	/* SUART */
