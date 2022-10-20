/*
 * special_structs.h
 *
 *  Created on: Oct 8, 2022
 *      Author: Tarık Kesen
 */

#ifndef INC_SPECIAL_STRUCTS_H_
#define INC_SPECIAL_STRUCTS_H_

#include "special_defines.h"
#include "special_enums.h"
#include "Ethernet/wizchip_conf.h"
#include "Internet/MQTT/MQTTClient.h"

struct inputVal {
	char inputLowDate[30];
	char inputHighDate[30];
};

struct productVal {
	struct inputVal mouldBackward;
	struct inputVal injectionForward;
	struct inputVal rawMaterialPacking;
	struct inputVal mouldForward;
	uint32_t productEndDate;
}*product;

typedef struct w5500_setup
{
	uint8_t bufSize[8];
	wiz_NetInfo netInfo;
	wiz_NetTimeout netTimeInfo;
}w5500_setup;

struct mqtt_client
{
	char* clientid;
	int nodelimiter;
	char* delimiter;
	enum QoS qos;
	char* username;
	char* password;
	char* host;
	int port;
	int showtopics;
};

#endif /* INC_SPECIAL_STRUCTS_H_ */
