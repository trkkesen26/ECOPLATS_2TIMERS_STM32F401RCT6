/*
 * special_enums.h
 *
 *  Created on: Oct 8, 2022
 *      Author: Tarık Kesen
 */

#ifndef INC_SPECIAL_ENUMS_H_
#define INC_SPECIAL_ENUMS_H_

typedef enum
{
	SET_RTC_NOK = -1,
	SET_RTC_OK = 1,
	GET_RTC_NOK = -2,
	GET_RTC_OK = 2
} RTC_StatusTypeDef;

typedef volatile enum
{
	SD_CARD_ERROR = -2,
	SD_CARD_BUSY = -1,
	SD_CARD_READY = 0,
	SD_CARD_NOT_READY
} SD_CARD_StatusTypeDef;

typedef enum
{
	ETHERNET_OK,
	ETHERNET_ERR,
	ETHERNET_CABLE_ERR,
	ETHERNET_CON_ERR,
	ETHERNET_CHIP_ERR
}ETHERNET_StatusTypeDef;

#endif /* INC_SPECIAL_ENUMS_H_ */
