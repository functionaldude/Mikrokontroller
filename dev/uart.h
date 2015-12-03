/**
 * @file uart.h
 *
 * @brief Low level driver specification for UART devices.
 *
 * @date $date$
 *
 * @author M.Lasagni
 *
 * $Id$
 */
#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

/**
 * @brief Initialize the UART module
 *
 * This function is called from the boot up code to initalize the UART module.
 *
 * @param baud_rate 	The baud rate of the connection.
 *
 */
void uart_init(uint32_t baud_rate);


#endif /* __UART_H__ */
