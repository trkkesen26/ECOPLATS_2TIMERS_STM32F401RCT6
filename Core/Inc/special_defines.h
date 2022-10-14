/*
 * special_defines.h
 *
 *  Created on: 7 Eki 2022
 *      Author: Tarık KESEN
 */

#ifndef INC_SPECIAL_DEFINES_H_
#define INC_SPECIAL_DEFINES_H_

/* DEVICE DEFINES */
#define DEVICE_ID			"003"
/* DEVICE DEFINES END */

/*
 * Input defines.
 * Going to read 8 of them. But only defined inputs going to be logged.
 */
#define MOULD_BACKWARD				0
#define INJECTION_FORWARD			1
#define RAW_MATERIAL_PACKING		2
#define INJECTION_BACKWARD			3
#define	MOULD_FORWARD				4

#define READ_INPUT_MOULD_BACKWARD				HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_0)
#define READ_INPUT_INJECTION_FORWARD			HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_1)
#define READ_INPUT_RAW_MATERIAL_PACKING			HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_2)
#define READ_INPUT_INJECTION_BACKWARD			HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_3)
#define READ_INPUT_MOULD_FORWARD				HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_4)
/* Input Defines End */

/* Private Defines */
#define bit(bit)		(1 << (bit))
#define print(v)		printf(#v"\r\n");

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')
/* Private Defines End */

/* MATH FUNC. Defines */
#define BCD2DEC(v)			((v/16*10) + (v%16))
#define DEC2BCD(v)			((v/10*16) + (v%10))
#define HEX2BCD(v)			((v) % 10 + (v) / 10 * 16)
#define BCD2HEX(v)			((v) % 16 + (v) / 16 * 10)
/* MATH FUNC. Defines End */

/* Arrays Size Defines */
#define PRODUCT_TIME_ARR_SIZE 		40
#define ETH_MAX_BUF_SIZE			2048
/* Arrays Size Defines End */

/* RTC Defines */
#define YEAR				   2000	// RTC will be set by getting 2 digits, so while printing||sending we need this.Change it when we are in 2100
/* RTC Defines End */

/* Logger Defines */
#define MSG_LOGGER		0b00000001    // 0b00000000 = Nothing, 0b00000001 = UART(printf), 0b00000010 = SD_CARD
#define UART_LOGGER		0b00000001
#define SD_LOGGER		0b00000010
/* Logger Defines End */

/* W5500 Defines */
#define _WIZCHIP_ 			5500
#define _WIZCHIP_IO_MODE_ 	_WIZCHIP_IO_MODE_SPI
#define ETHERNET_CHIP		"W5500"

#define ETH_RESET_PIN_PORT		GPIOD
#define ETH_RESET_PIN			GPIO_PIN_2
#define ETH_PWR_RESET			HAL_GPIO_WritePin(ETH_RESET_PIN_PORT, ETH_RESET_PIN, 0)
#define ETH_PWR_SET				HAL_GPIO_WritePin(ETH_RESET_PIN_PORT, ETH_RESET_PIN, 1)
/* W5500 Defines End*/

/* Printf Defines */
#if defined(__GNUC__)
int _write(int fd, char * ptr, int len)
{
  HAL_UART_Transmit(&huart1, (uint8_t *) ptr, len, HAL_MAX_DELAY);
  return len;
}
#elif defined (__ICCARM__)
	#include "LowLevelIOInterface.h"
	size_t __write(int handle, const unsigned char * buffer, size_t size)
	{
	  HAL_UART_Transmit(&huart1, (uint8_t *) buffer, size, HAL_MAX_DELAY);
	  return size;
	}
#elif defined (__CC_ARM)
	int fputc(int ch, FILE *f)
	{
		HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
		return ch;
	}
#endif

#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
/* Printf Defines End */

/* SD_CARD Defines */
#define SD_READ_BUF_SIZE	500
/* SD_CARD Defines End*/

#endif /* INC_SPECIAL_DEFINES_H_ */
