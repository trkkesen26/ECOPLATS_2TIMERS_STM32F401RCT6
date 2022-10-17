/* USER CODE BEGIN Header */
/*
 * TODO LIST FOR DEVELOPT
 * - Thermocouple values will need to be included.
 * - Timer1 ==> Handle inputs & product status. Then save to sd card.
 * - Timer2 ==> Handle w5500 & connection status. Then get data from sd card and send to rabbitmq.
 *
 */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "special_typedefs.h"
#include "special_defines.h"
#include "special_structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "Internet/SNTP/sntp.h"
#include "Ethernet/wizchip_conf.h"
#include "Ethernet/socket.h"
#include "Application/loopback/loopback.h"
#include "Ethernet/W5500/w5500.h"
#include "Internet/MQTT/MQTTClient.h"
#include <time.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
TIMER timer3Counter;
TIMER timer4Counter;

SD_CARD_StatusTypeDef sdStatus;
ETHERNET_StatusTypeDef w5500Status;
RTC_StatusTypeDef rtcStatus = SET_RTC_NOK;

FATFS fs;
FIL fil;
FRESULT fresult;
DIR dir;
FILINFO fno;

w5500_setup w5500opt = {
		  .bufSize = {2,2,2,2,2,2,2,2},
		  .netInfo = {   .mac 	= {0x00, 0x08, 0xff, 0xab, 0xcd, 0x01},					// Mac address
	  	  	  	  	     .ip 	= {192, 168, 1, 200},									// IP address
						 .sn 	= {255, 255, 255, 0},										// Subnet mask
						 .gw 	= {192, 168, 1, 1},									// Gateway address
		  },
		  .netTimeInfo = {
					.retry_cnt = 3,		 // 100ms, 200ms, 400ms, 800ms, 1600ms
					.time_100us = 1000,  // 200ms, 400ms, 800ms, 1600 ms, 3200ms  ==> 6.2 sn
		  }
};

/*
 -username : ithinka
 -password : 7pnmBHXE2ZQNiqjmj_EW
 */
char hostIp[4] = {192, 168, 1, 47};
unsigned char tempBuffer[1024*2] = {};

struct mqtt_client mqttopt = {
		  .clientid = "denemeClient",
		  .nodelimiter = 0,
		  .delimiter = "\n",
		  .qos = QOS0,
		  .username = "stm32",
		  .password = "stm32",
		  .host = hostIp,
		  .port = 1883,
		  .showtopics = 1
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint8_t currentInputs = 0b00000000;
volatile uint8_t prevInputs    = 0b00000000;

volatile uint8_t currentProductStatus = 0;
volatile uint8_t currentTimer3Status = 0;
volatile uint8_t currentTimer4Status = 0;

volatile bool IsProductDone = true;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void checkInputs(void);
int checkProduct(void);
void msgLogger (char*);
RTC_StatusTypeDef setRTCTime(void);
uint8_t dayOfWeek(uint8_t, uint8_t, uint8_t);
char* getRTCTime(void);
char* getLogTime(void);
char* getDataTime(void);
char* getRTCStatus(RTC_StatusTypeDef status);
void fillProduct(struct productVal *product);
bool writeSDProductInfo(struct productVal *product);
SD_CARD_StatusTypeDef SDInit(void);
int8_t w5500Init(struct w5500_setup w5500Opt);
bool checkSDStore(void);
int MQTT_run(char* sdBuf);
void inputStatusLogger(uint8_t);
void cs_sel();
void cs_desel();
uint8_t spi_rb(void);
void spi_wb(uint8_t b);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t ntp_server[4] = {176, 235, 22, 135};
uint8_t ntpSocket = 0;
uint8_t timeZone = 28;
unsigned char ethBuf[ETH_MAX_BUF_SIZE];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_SPI2_Init();
  MX_FATFS_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  sdStatus = SDInit();
  if (sdStatus == SD_CARD_READY) {
	  msgLogger("SD_CARD Init is done.");
  }
  reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
  reg_wizchip_spi_cbfunc(spi_rb, spi_wb);

  prevInputs = GPIOB->IDR;
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start_IT(&htim3);

  msgLogger("Setup is DONE.");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3) {
		if (currentTimer3Status == 0) {
			product = (struct productVal*)malloc(sizeof(struct productVal));
			if (product != NULL) {
				fillProduct(product);
				currentTimer3Status = 1;
				msgLogger("Timer3 status is changed. 0 --> 1");
			}
			else
				currentTimer3Status = 0;
		}
		else if (currentTimer3Status == 1) {
			checkInputs();
			int productStatus = checkProduct();
			if (productStatus) {
				currentTimer3Status = 2;
				msgLogger("Timer3 status is changed. 1 --> 2");
			}
		}
		else if (currentTimer3Status == 2) {
			free(product);
			IsProductDone = true;
			currentTimer3Status = 0;
			msgLogger("Timer3 status is changed. 2 --> 0");
		}
	}
	if (htim->Instance == TIM4) {
		timer4Counter++;
		if (currentTimer4Status == 0) {
			ETH_PWR_RESET;
			currentTimer4Status = 1;
			msgLogger("Timer4 status is changed. 0 --> 1");
		}
		else if (currentTimer4Status == 1) {
			ETH_PWR_SET;
			currentTimer4Status = 2;
			msgLogger("Timer4 status is changed. 1 --> 2");
		}
		else if (currentTimer4Status == 2) {
			if (w5500Init(w5500opt) == 0) {
				msgLogger("W5500 init OK.");
				currentTimer4Status = 3;
				msgLogger("Timer4 status is changed. 2 --> 3");
			}
			else {
				currentTimer4Status = 0;
				msgLogger("W5500 Init Error. Timer4 status is changed. 2 --> 0");
			}
		}
		else if (currentTimer4Status == 3) {
			currentTimer4Status = 4;
			msgLogger("Timer4 status is changed. 3 --> 4");
		}
		else if (currentTimer4Status == 4) {
			currentTimer4Status = 5;
			msgLogger("Timer4 status is changed. 4 --> 5");
		}
		else if (currentTimer4Status == 5) {
			static int counter = 0;
			if (rtcStatus == SET_RTC_NOK) {
				if (timer4Counter % 2 == 0) {    //to make 2 seconds delay
					SNTP_init(ntpSocket, ntp_server, timeZone, ethBuf);
					if (SET_RTC_OK == setRTCTime()) {
						rtcStatus = SET_RTC_OK;
						printf("Time is succesfully set to = %s\r\n", getRTCTime());
						currentTimer4Status = 6;
						msgLogger("Timer4 status is changed. 5 --> 6");
						counter = 0;
					}
					else {
						msgLogger("setRTCTime Error");
						counter++;
						if (counter > 10) {
							msgLogger("setRTCTime Error happaned too many times.");
							counter = 0;
							currentTimer4Status = 0;
							msgLogger("Timer4 status is changed. 5 --> 0");
						}
					}
				}
			}
		}
		else if (currentTimer4Status == 6) {
			if (IsProductDone) {
				currentTimer4Status = 7;
				msgLogger("Timer4 status is changed. 6 --> 7");
			}
		}
		else if (currentTimer4Status == 7) {
			if (sdStatus == SD_CARD_READY) {
				if (checkSDStore()) {
					currentTimer4Status = 6;
					msgLogger("Timer4 status is changed. 7 --> 6");
				}
				else {
					currentTimer4Status = 0;
					msgLogger("Timer4 status is changed. 7 --> 0");
				}
			}
			if (!IsProductDone) {
				currentTimer4Status = 6;
				msgLogger("Timer4 status is changed. 7 --> 6");
			}
		}
	}
}

void checkInputs(void)
{
	currentInputs = GPIOB->IDR;
	if (prevInputs != currentInputs) {
		inputStatusLogger(currentInputs);
		prevInputs = currentInputs;
	}
}

int checkProduct(void)
{
	switch(currentProductStatus) {
	case 0:
		if (((currentInputs & bit(MOULD_BACKWARD)) == bit(MOULD_BACKWARD)) == true) {
			strcpy(product->mouldBackward.inputHighDate, getRTCTime());
			currentProductStatus = 1;
			msgLogger("Current product status is changed. 0 --> 1");
		}
		break;
	case 1:
		if (((currentInputs & bit(MOULD_BACKWARD)) == bit(MOULD_BACKWARD)) == false) {
			strcpy(product->mouldBackward.inputLowDate, getRTCTime());
			currentProductStatus = 2;
			msgLogger("Current product status is changed. 1 --> 2");
		}
		else {
			if (((currentInputs & bit(MOULD_FORWARD)) == bit(MOULD_FORWARD)) == true) {
				strcpy(product->productEndDate, getDataTime());
				currentProductStatus = 0;
				msgLogger("Current state is 0. Unexpected behavior has been detected.");
				product->pInfo = PRODUCT_ERROR;
				return 1;
			}
		}
		break;
	case 2:
		if (((currentInputs & bit(INJECTION_FORWARD)) == bit(INJECTION_FORWARD)) == true) {
			strcpy(product->injectionForward.inputHighDate, getRTCTime());
			currentProductStatus = 3;
			msgLogger("Current product status is changed. 2 --> 3");
		}
		else {
			if (((currentInputs & bit(MOULD_FORWARD)) == bit(MOULD_FORWARD)) == true) {
				strcpy(product->productEndDate, getDataTime());
				product->pInfo = PRODUCT_ERROR;
				currentProductStatus = 0;
				msgLogger("Current state is 0. Unexpected behavior has been detected.");
				return 2;
			}
		}
		break;
	case 3:
		if (((currentInputs & bit(INJECTION_FORWARD)) == bit(INJECTION_FORWARD)) == false) {
			strcpy(product->injectionForward.inputLowDate, getRTCTime());
			currentProductStatus = 4;
			msgLogger("Current product status is changed. 3 --> 4");
		}
		else {
			if (((currentInputs & bit(MOULD_FORWARD)) == bit(MOULD_FORWARD)) == true) {
				strcpy(product->productEndDate, getDataTime());
				product->pInfo = PRODUCT_ERROR;
				currentProductStatus = 0;
				msgLogger("Current state is 0. Unexpected behavior has been detected.");
				return 3;
			}
		}
		break;
	case 4:
		if (((currentInputs & bit(RAW_MATERIAL_PACKING)) == bit(RAW_MATERIAL_PACKING)) == true) {
			strcpy(product->rawMaterialPacking.inputHighDate, getRTCTime());
			currentProductStatus = 5;
			msgLogger("Current product status is changed. 4 --> 5");
			IsProductDone = false;
		}
		else {
			if (((currentInputs & bit(MOULD_FORWARD)) == bit(MOULD_FORWARD)) == true) {
				strcpy(product->productEndDate, getDataTime());
				product->pInfo = PRODUCT_ERROR;
				currentProductStatus = 0;
				msgLogger("Current state is 0. Unexpected behavior happaned.");
				return 4;
			}
		}
		break;
	case 5:
		if (((currentInputs & bit(RAW_MATERIAL_PACKING)) == bit(RAW_MATERIAL_PACKING)) == false) {
			strcpy(product->rawMaterialPacking.inputLowDate, getRTCTime());
			currentProductStatus = 6;
			msgLogger("Current product status is changed. 5 --> 6");
		}
		else {
			if (((currentInputs & bit(MOULD_FORWARD)) == bit(MOULD_FORWARD)) == true) {
				strcpy(product->productEndDate, getDataTime());
				product->pInfo = PRODUCT_ERROR;
				currentProductStatus = 0;
				msgLogger("Current state is 0. Unexpected behavior has been detected.");
				return 5;
			}
		}
		break;
	case 6:
		if (((currentInputs & bit(MOULD_FORWARD)) == bit(MOULD_FORWARD)) == true) {
			strcpy(product->mouldForward.inputHighDate, getRTCTime());
			currentProductStatus = 7;
			msgLogger("Current product status is changed. 6 --> 7");
		}
		else {
			if (((currentInputs & bit(MOULD_BACKWARD)) == bit(MOULD_BACKWARD)) == true) {
				strcpy(product->productEndDate, getDataTime());
				product->pInfo = PRODUCT_ERROR;
				currentProductStatus = 0;
				msgLogger("Current state is 0. Unexpected behavior has been detected.");
				return 6;
			}
		}
		break;
	case 7:
		if (((currentInputs & bit(MOULD_FORWARD)) == bit(MOULD_FORWARD)) == false) {
			strcpy(product->mouldForward.inputLowDate, getRTCTime());
			strcpy(product->productEndDate, getDataTime());
			product->pInfo = PRODUCT_PRODUCED;
			currentProductStatus = 0;
			msgLogger("Product produced succesfully.");
			int sdResult = writeSDProductInfo(product);
			if (sdResult)
				msgLogger("Data is created on SD CARD.");
			return 8;
		}
		else {
			if (((currentInputs & bit(MOULD_BACKWARD)) == bit(MOULD_BACKWARD)) == true) {
				strcpy(product->productEndDate, getDataTime());
				product->pInfo = PRODUCT_ERROR;
				currentProductStatus = 0;
				msgLogger("Current state is 0. Unexpected behavior has been detected.");
				return 7;
			}
		}
		break;
	}
	return 0;
}

void fillProduct(struct productVal *product)
{
	product->pInfo = PRODUCT_ERROR;
	strcpy(product->injectionForward.inputHighDate, "null");
	strcpy(product->injectionForward.inputLowDate, "null");
	strcpy(product->mouldBackward.inputHighDate, "null");
	strcpy(product->mouldBackward.inputLowDate, "null");
	strcpy(product->mouldForward.inputHighDate, "null");
	strcpy(product->mouldForward.inputLowDate, "null");
	strcpy(product->rawMaterialPacking.inputHighDate, "null");
	strcpy(product->rawMaterialPacking.inputLowDate, "null");
	strcpy(product->productEndDate, "null");
}

bool writeSDProductInfo(struct productVal *product)
{
	char *result = (char*)malloc(4 * (sizeof(int)));
	if (result == NULL) {
		printf("[writeSDProductInfo()] Memory Allocation Error!!!");
		return false;
	}
	char *mback  = (char*)malloc(150 * (sizeof(char)));
	if (mback == NULL) {
		printf("[writeSDProductInfo()] Memory Allocation Error!!!");
		free(result);
		return false;
	}
	char *mforw  = (char*)malloc(150 * (sizeof(char)));
	if (mforw == NULL) {
		printf("[writeSDProductInfo()] Memory Allocation Error!!!");
		free(result); free(mback);
		return false;
	}
	char *iforw  = (char*)malloc(150 * (sizeof(char)));
	if (iforw == NULL) {
		printf("[writeSDProductInfo()] Memory Allocation Error!!!");
		free(result); free(mback); free(mforw);
		return false;
	}
	char *rmet   = (char*)malloc(150 * (sizeof(char)));
	if (rmet == NULL) {
		printf("[writeSDProductInfo()] Memory Allocation Error!!!");
		free(result); free(mback); free(mforw); free(iforw);
		return false;
	}

	if (sdStatus == SD_CARD_READY) {
		sdStatus = SD_CARD_BUSY;
		char fileName[50];
		if (strlen(product->productEndDate) > 5) {
			sprintf(fileName, "Data/%s.log", product->productEndDate);
		} else {
			sprintf(fileName, "Data/%s_Err.log", getLogTime());
		}
		fresult = f_open(&fil, fileName, FA_OPEN_ALWAYS | FA_WRITE);
		if (fresult == FR_OK) {
			sprintf(result, "\"result\": %d", product->pInfo);
			sprintf(mback, ", \"mback\": { \"inputHighDate\": \"%s\", \"inputLowDate\": \"%s\" }", product->mouldBackward.inputHighDate, product->mouldBackward.inputLowDate);
			sprintf(mforw, ", \"mforw\": { \"inputHighDate\": \"%s\", \"inputLowDate\": \"%s\" }", product->mouldForward.inputHighDate, product->mouldForward.inputLowDate);
			sprintf(iforw, ", \"iforw\": { \"inputHighDate\": \"%s\", \"inputLowDate\": \"%s\" }", product->injectionForward.inputHighDate, product->injectionForward.inputLowDate);
			sprintf(rmet, ", \"rmet\": { \"inputHighDate\": \"%s\", \"inputLowDate\": \"%s\" }", product->rawMaterialPacking.inputHighDate, product->rawMaterialPacking.inputLowDate);
			char* data = (char*)malloc(150 * 5 * (sizeof(char)));
			if (data != NULL) {
				sprintf(data, "{%s%s%s%s%s}", result, mback, mforw, iforw, rmet);
				f_puts(data, &fil);
				free(result); free(mback); free(mforw); free(iforw); free(rmet);
				free(data);
				f_close(&fil);
				sdStatus = SD_CARD_READY;
				return true;
			}
			else {
				free(result); free(mback); free(mforw); free(iforw); free(rmet);
				printf("[writeSDProductInfo()] Memory Allocation Error. \r\n");
				f_close(&fil);
				sdStatus = SD_CARD_READY;
				return false;
			}
		}
		else {
			free(result); free(mback); free(mforw); free(iforw); free(rmet);
			printf("[writeSDProductInfo()] Error happaned while opening file.\r\n");
			sdStatus = SD_CARD_READY;
			return false;
		}
	}
	else {
		free(result); free(mback); free(mforw); free(iforw); free(rmet);
		return false;
	}

	return false;
}

RTC_StatusTypeDef setRTCTime()  //timeBuf is gonna have ["day" = 0, "month" = 1, "year" = 2, "hour" = 3, "min" = 4, "second" = 5]
{
	uint8_t status;
	datetime ntpTime;
	status = SNTP_run(&ntpTime);
	// check rtc.c if there is added new sDate and sTime
	if (status) {
		RTC_TimeTypeDef sTime = {0};
		RTC_DateTypeDef sDate = {0};

		sTime.Hours = DEC2BCD(ntpTime.hh);
		sTime.Minutes = DEC2BCD(ntpTime.mm);
		sTime.Seconds = DEC2BCD(ntpTime.ss);
		sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
		sTime.StoreOperation = RTC_STOREOPERATION_RESET;
		if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
		{
			Error_Handler();
		}
		sDate.Date = DEC2BCD(ntpTime.dd);
		sDate.Month = DEC2BCD(ntpTime.mo);
		sDate.Year = DEC2BCD(ntpTime.yy%100);
		sDate.WeekDay = DEC2BCD(dayOfWeek(ntpTime.dd, ntpTime.mo, ntpTime.yy));  // d, m, y
		if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
		{
			Error_Handler();
		}
		return SET_RTC_OK;
	}
	else return SET_RTC_NOK;
}

char* getRTCTime(void)
{
	RTC_TimeTypeDef gTime;
	RTC_DateTypeDef gDate;

	static char getTimeBuf[30] = {'\0'};

	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BCD);

	sprintf(getTimeBuf, "%02d/%02d/%04d,%02d:%02d:%02d", BCD2DEC(gDate.Date), BCD2DEC(gDate.Month), BCD2DEC(gDate.Year) + YEAR, BCD2DEC(gTime.Hours), BCD2DEC(gTime.Minutes), BCD2DEC(gTime.Seconds));
						//format can be changed by what developers want.
	return getTimeBuf;
}

char* getLogTime(void)
{
	RTC_TimeTypeDef gTime;
	RTC_DateTypeDef gDate;

	static char getTimeBuf[30] = {'\0'};

	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BCD);

	sprintf(getTimeBuf,"%02d_%02d_%04d", BCD2DEC(gDate.Date), BCD2DEC(gDate.Month), BCD2DEC(gDate.Year) + YEAR);
						//format can be changed by what developers want.
	return getTimeBuf;
}

char* getDataTime(void)
{
	RTC_TimeTypeDef gTime;
	RTC_DateTypeDef gDate;

	static char getTimeBuf[30] = {'\0'};

	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BCD);

	sprintf(getTimeBuf, "%02d_%02d_%04dT%02d_%02d_%02d", BCD2DEC(gDate.Date), BCD2DEC(gDate.Month), BCD2DEC(gDate.Year) + YEAR, BCD2DEC(gTime.Hours), BCD2DEC(gTime.Minutes), BCD2DEC(gTime.Seconds));
						//format can be changed by what developers want.
	return getTimeBuf;
}

uint8_t dayOfWeek(uint8_t d, uint8_t m, uint8_t y)
{
	//this is zero-based algorithm. So sunday is 0 monday is 1 etc.
	uint8_t weekDay = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
	if (weekDay == 0) return 7;
	else return weekDay;
}

char* getRTCStatus(RTC_StatusTypeDef status)
{
	switch(status)
	{
		case -1:
			return "SET_RTC_NOK";
		case 1:
			return "SET_RTC_OK";
		case -2:
			return "GET_RTC_NOK";
		case 2:
			return "GET_RTC_OK";
		default:
			return "NOTHING";
	}
	return "NOTHING";
}

SD_CARD_StatusTypeDef SDInit(void)
{
	fresult = f_mount(&fs, "", 0);
	if (FR_OK != fresult) {
		return SD_CARD_ERROR;
	}
	fresult = f_mkdir("Data");
	if (FR_OK != fresult && FR_EXIST != fresult) {
		return SD_CARD_ERROR;
	}
	fresult = f_mkdir("Log");
	if (FR_OK != fresult && FR_EXIST != fresult) {
		return SD_CARD_ERROR;
	}

	return SD_CARD_READY;
}

bool checkSDStore(void)
{
	sdStatus = SD_CARD_BUSY;
	fresult = f_findfirst(&dir, &fno, "Data", "????*.log");
	if (strlen(fno.fname) > 1 && fresult == FR_OK) {
		char fileName[sizeof(fno.fname) + 20];
		sprintf(fileName, "Data/%s", fno.fname);
		fresult = f_open(&fil, fileName, FA_READ);
		char buf[SD_READ_BUF_SIZE];
		f_gets(buf, sizeof(buf), &fil);
		int result = MQTT_run(buf);
		if (result < 0) {
			msgLogger("Error Happaned While Sending Data to MQTT Server.");
			sdStatus = SD_CARD_READY;
			fresult = f_close(&fil);
			return false;
		}
		else {
			msgLogger("Data has been sent succesfully.");
			fresult = f_close(&fil);
			f_unlink(fileName);
		}
	}
	sdStatus = SD_CARD_READY;
	return true;
}

int8_t w5500Init(struct w5500_setup w5500Opt)
{
	int8_t result;
	result = wizchip_init(w5500Opt.bufSize, w5500Opt.bufSize);
	wizchip_setnetinfo(&w5500Opt.netInfo);
	wizchip_settimeout(&w5500Opt.netTimeInfo);
	return result;
}

int MQTT_run(char* sdBuf)
{
	int rc = 0;
	uint8_t buf[SD_READ_BUF_SIZE];
	char pubbuf[SD_READ_BUF_SIZE];
	Network n;
	MQTTClient c;
	MQTTMessage m;

	NewNetwork(&n, 0);
	int i =	ConnectNetwork(&n, (uint8_t*)hostIp, 1883);
	if (i == 0) return -1;
	MQTTClientInit(&c, &n, 1000, buf, sizeof(buf), tempBuffer, sizeof(tempBuffer));

	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	data.willFlag = 0;
	data.MQTTVersion = 3;
	data.clientID.cstring = mqttopt.clientid;
	data.username.cstring = mqttopt.username;
	data.password.cstring = mqttopt.password;

	data.keepAliveInterval = 60;
	data.cleansession = 1;

	rc = MQTTConnect(&c, &data);
	if (rc < 0) {
		return rc;
	}
	printf("Connected to server : {%d, %d, %d, %d}\r\n", hostIp[0], hostIp[1], hostIp[2], hostIp[3]);
	mqttopt.showtopics = 1;

	m.qos = QOS0;
	m.retained = 1;
	m.dup = 0;

	MQTTYield(&c, data.keepAliveInterval);
	sprintf(pubbuf, sdBuf);
	m.payload = pubbuf;
	m.payloadlen = strlen(pubbuf);
	uint8_t mqttTOPIC[30] = "/product_003";
	rc = -1;
	uint8_t retry = 0;
	while (rc != 0) {
		retry++;
		rc = MQTTPublish(&c, (const char*)mqttTOPIC, &m);
		if (retry > 4) return rc;
	}
	printf("Message is sent to MQTT Server.\r\n");
	return rc;
}

void msgLogger (char* msg)
{
#if MSG_LOGGER & UART_LOGGER
	uint32_t len = strlen(msg);
	printf("[%s] ==> %s\n", getRTCTime(), msg);
	if (len > 2000) return;
	#if MSG_LOGGER & SD_LOGGER
		char *ptrBuf = (char*)malloc(len * sizeof(char));
		if (ptrBuf == NULL) {
			printf("[%s] ==> %s\n", getRTCTime(), "Can't allocate memory for debug");
			return;
		}
		if (sdStatus == SD_CARD_READY) {
			sdStatus = SD_CARD_BUSY;
		    fresult = f_mkdir("Logs");
		    if (fresult == FR_EXIST) {
		    	printf("LOG File is already exited.\n");
		    }
		    else if (fresult != FR_OK) {
		    	printf("Error Happaned while opening Dictionary! Fresult = %d\n", fresult);
		    	free(ptrBuf);
		    	return;
		    }
		  	else {
		  		printf("Log directory is created.\n");
		  	}
			char fileName[40];
			sprintf(fileName, "Logs/%s.log", getLogTime());
			fresult = f_open(&fil, fileName, FA_OPEN_APPEND | FA_WRITE);
			if (fresult == FR_OK) {
				sprintf(ptrBuf, "%s ==> %s\n", getRTCTime(), msg);
				f_puts(ptrBuf, &fil);
				f_close(&fil);
			}
			free(ptrBuf);
		}
		else {
			free(ptrBuf);
		}
		sdStatus = SD_CARD_READY;
	#endif
#endif
}

void inputStatusLogger(uint8_t input)
{
	#if MSG_LOGGER & UART_LOGGER
		char buf[sizeof("Current Inputs ==> ") + sizeof(int)];
		sprintf(buf, "Current Inputs ==> "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(input));
		msgLogger(buf);
	#endif
}

void cs_sel() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //CS LOW
}

void cs_desel() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); //CS HIGH
}

uint8_t spi_rb(void) {
	uint8_t rbuf;
	HAL_SPI_Receive(&hspi1, &rbuf, 1, 0xFFFFFFFF);
	return rbuf;
}

void spi_wb(uint8_t b) {
	HAL_SPI_Transmit(&hspi1, &b, 1, 0xFFFFFFFF);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
