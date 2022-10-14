/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI1_ETHERNET_CS_Pin GPIO_PIN_4
#define SPI1_ETHERNET_CS_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define MOLD_BACKWARD_INPUT_Pin GPIO_PIN_0
#define MOLD_BACKWARD_INPUT_GPIO_Port GPIOB
#define INJECTION_FORWARD_INPUT_Pin GPIO_PIN_1
#define INJECTION_FORWARD_INPUT_GPIO_Port GPIOB
#define RAW_MATERIAL_INPUT_Pin GPIO_PIN_2
#define RAW_MATERIAL_INPUT_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_12
#define SD_CS_GPIO_Port GPIOB
#define SD_SCK_Pin GPIO_PIN_13
#define SD_SCK_GPIO_Port GPIOB
#define SD_MISO_Pin GPIO_PIN_14
#define SD_MISO_GPIO_Port GPIOB
#define SD_MOSI_Pin GPIO_PIN_15
#define SD_MOSI_GPIO_Port GPIOB
#define ETHERNET_RST_Pin GPIO_PIN_2
#define ETHERNET_RST_GPIO_Port GPIOD
#define INJECTION_BACKWARD_INPUT_Pin GPIO_PIN_3
#define INJECTION_BACKWARD_INPUT_GPIO_Port GPIOB
#define MOLD_FORWARD_INPUT_Pin GPIO_PIN_4
#define MOLD_FORWARD_INPUT_GPIO_Port GPIOB
#define REVIZED_1_INPUT_Pin GPIO_PIN_5
#define REVIZED_1_INPUT_GPIO_Port GPIOB
#define REVIZED_2_INPUT_Pin GPIO_PIN_6
#define REVIZED_2_INPUT_GPIO_Port GPIOB
#define REVIZED_3_INPUT_Pin GPIO_PIN_7
#define REVIZED_3_INPUT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
