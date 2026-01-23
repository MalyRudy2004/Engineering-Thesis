/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "gpio_init.h"
#include "usart_init.h"
#include "adc_init.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define comp (GPIOB -> IDR)
#define checkCOMP1 (comp & COMP1mask)
#define checkCOMP2 (comp & COMP2mask)
#define checkCOMP3 (comp & COMP3mask)
#define checkCOMP4 (comp & COMP4mask)
#define checkA1 (!checkCOMP1 && !checkCOMP2 &&  checkCOMP3 && !checkCOMP4)
#define checkA2 (!checkCOMP1 &&  checkCOMP2 &&  checkCOMP3 && !checkCOMP4)
#define checkA3 ( checkCOMP1 && !checkCOMP2 &&  checkCOMP3 &&  checkCOMP4)
#define checkA4 ( checkCOMP1 && !checkCOMP2 &&  checkCOMP3 && !checkCOMP4)
#define checkA5 ( checkCOMP1 && !checkCOMP2 && !checkCOMP3 && !checkCOMP4)
#define checkB1 (!checkCOMP1 && !checkCOMP2 &&  checkCOMP3 &&  checkCOMP4)
#define checkB2 (!checkCOMP1 &&  checkCOMP2 &&  checkCOMP3 &&  checkCOMP4)
#define checkB3 ( checkCOMP1 &&  checkCOMP2 &&  checkCOMP3 &&  checkCOMP4)
#define checkB4 ( checkCOMP1 &&  checkCOMP2 &&  checkCOMP3 && !checkCOMP4)
#define checkB5 ( checkCOMP1 &&  checkCOMP2 && !checkCOMP3 && !checkCOMP4)
#define checkC1 (!checkCOMP1 && !checkCOMP2 && !checkCOMP3 &&  checkCOMP4)
#define checkC2 ( checkCOMP1 && !checkCOMP2 && !checkCOMP3 &&  checkCOMP4)
#define checkC3 ( checkCOMP1 &&  checkCOMP2 && !checkCOMP3 &&  checkCOMP4)
#define checkC4 (!checkCOMP1 &&  checkCOMP2 && !checkCOMP3 &&  checkCOMP4)
#define checkC5 (!checkCOMP1 &&  checkCOMP2 && !checkCOMP3 && !checkCOMP4)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  uint8_t calfact1, calfact2;
  clock_enable();
  gpio_comp_init();
  usart2_init();
  adc_cal(ADC1, &calfact1);
  adc_cal(ADC2, &calfact2);
  adc_init();
  clear_terminal();

  char uart_buf[64];
  void check(uint32_t state, uint8_t tile, char pos[8])
  {
	  if (state)
	  {
		  clear_terminal();
		  map(tile);
		  adc_read(uart_buf);
		  send_string(uart_buf);
		  send_string(pos);
		  //send_backspace();
		  //send_backspace();
		  HAL_Delay(500);
	  }
  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (checkA1)
	  {
		  HAL_Delay(200);
		  check (checkA1, A1, A1pos);
	  }
	  else if (checkA2)
  	  {
  		  HAL_Delay(200);
  		  check (checkA2, A2, A2pos);
  	  }
	  else if (checkA3)
  	  {
  		  HAL_Delay(200);
  		  check (checkA3, A3, A3pos);
  	  }
	  else if (checkA4)
  	  {
  		  HAL_Delay(200);
  		  check (checkA4, A4, A4pos);
  	  }
	  else if (checkA5)
  	  {
  		  HAL_Delay(200);
  		  check (checkA5, A5, A5pos);
  	  }
	  else if (checkB1)
	  {
		  HAL_Delay(200);
		  check (checkB1, B1, B1pos);
	  }
	  else if (checkB2)
  	  {
  		  HAL_Delay(200);
  		  check (checkB2, B2, B2pos);
  	  }
	  else if (checkB3)
  	  {
  		  HAL_Delay(200);
  		  check (checkB3, B3, B3pos);
  	  }
	  else if (checkB4)
  	  {
  		  HAL_Delay(200);
  		  check (checkB4, B4, B4pos);
  	  }
	  else if (checkB5)
  	  {
  		  HAL_Delay(200);
  		  check (checkB5, B5, B5pos);
  	  }
	  else if (checkC1)
	  {
		  HAL_Delay(200);
		  check (checkC1, C1, C1pos);
	  }
	  else if (checkC2)
  	  {
  		  HAL_Delay(200);
  		  check (checkC2, C2, C2pos);
  	  }
	  else if (checkC3)
  	  {
  		  HAL_Delay(200);
  		  check (checkC3, C3, C3pos);
  	  }
	  else if (checkC4)
  	  {
  		  HAL_Delay(200);
  		  check (checkC4, C4, C4pos);
  	  }
	  else if (checkC5)
  	  {
  		  HAL_Delay(200);
  		  check (checkC5, C5, C5pos);
  	  }
	  else
	  {
		  clear_terminal();
	  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */


/* USER CODE BEGIN 4 */

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
#ifdef USE_FULL_ASSERT
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
