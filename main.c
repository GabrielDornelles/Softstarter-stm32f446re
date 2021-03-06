/* USER CODE BEGIN Header */

/*
 Autor: Gabriel Dornelles Monteiro, Vitor Bierhals
 Turma :4423
 Eletr�nica de pot�ncia
 Professor: Irineu Alfredo Ronconi
 Trabalho: Softstarter
 */

/**
 *
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2019 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdio.h"
#include "stdlib.h"
#include "lcd.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim11;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

		int ts_dez=0;
		int ts_un=0;
		int ts_time=0;
		int td_dez=0;
		int td_un=0;
		int td_time=0;
		int CNTstop = 10, CNTstart = 10;
		int PPM = 0;
		int x = 0, y = 0, z = 0;
		int selecao = 1;
		int segundostart = 5, segundostop = 5;

		unsigned char Data[4];
		unsigned char Data2;

		float segundosreal = 0, rPPM = 0, rtimes = 5, rtimep = 5;

		_Bool preflag=0;
		_Bool flag_delay=0;
		_Bool flag_ligado = 0;
		_Bool flag_sobrecorrente=0;
		_Bool repique = 1, repique2 = 1, preselecao = 1, soft = 0;
		_Bool incrementa = 0;
		_Bool start = 0, stop = 0, run = 0;
		_Bool fZCD = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM11_Init(void);
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
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */

	lcd_init();
	HAL_UART_Init(&huart2);
	HAL_UART_Receive_IT(&huart2,Data,4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {

		//HAL_TIM_Base_Start_IT(&htim1);
//lcd_goto(0xc2);
//lcd_printd(variavel_teste);
//lcd_goto(0xca);
//lcd_printd(segundostart);



		if (repique == 0) {
			HAL_Delay(300);
			repique = 1;
		}

		if (repique2 == 0) {
			HAL_Delay(200);
			repique2 = 1;
		}

		if (selecao == 1) {
			if(segundostart<5) segundostart =5;
			preselecao = 0;
			soft=0;
			lcd_goto(0x80);
			lcd_puts("Tempo de subida ");

			lcd_goto(0xC0);
			lcd_puts("    Tempo:");

				lcd_goto(0xCA);
				lcd_printd(segundostart);
				lcd_goto(0xCC);
				lcd_puts("    ");

				CNTstart = segundostart * 2;

				rtimes = segundostart;
				rtimes = rtimes / 180;

			} else __NOP();


		if (selecao == 2) {

			if(segundostop<5) segundostop = 5;
			preselecao = 0;
			lcd_goto(0x80);
			lcd_puts("Tempo de descida");

			lcd_goto(0xC0);
			lcd_puts("    Tempo:");


				lcd_goto(0xCA);
				lcd_printd(segundostop);
				lcd_goto(0xcc);
				lcd_puts("    ");

				CNTstop = segundostop * 2;

				rtimep = segundostop;
				rtimep = rtimep / 180;

			} else __NOP();

		if (selecao == 3 && preselecao == 1 && flag_sobrecorrente == 0) {

			HAL_TIM_Base_Start_IT(&htim3);
			preselecao = 0;
			soft = 1;
			start = 1;
			PPM = 150;

			lcd_goto(0x80);
			lcd_puts("     LIGANDO    ");
			lcd_goto(0xC0);
			lcd_puts("                      ");

		}

		if (selecao == 3 && flag_sobrecorrente == 0) {
			flag_ligado = 1;
			if (run == 1 && flag_sobrecorrente == 0) {
				lcd_goto(0x80);
				lcd_puts("     LIGADO     ");
				//preflag=1;
				HAL_GPIO_WritePin(BYPASS_GPIO_Port, BYPASS_Pin, 1);
				if(HAL_GPIO_ReadPin(GPIOC, BYPASS_Pin)==1)
				{

					if(flag_delay==0)
					{
						HAL_Delay(3000);
						flag_delay=1;
					}

					preflag=1;
				}
			}


		} else
			__NOP();

		if (selecao == 4 && preselecao == 1) {
			preflag=0;
			preselecao = 0;
			stop = 1;
			PPM = 40;
			HAL_TIM_Base_Start_IT(&htim3);
			lcd_goto(0x80);
			lcd_puts("   DESLIGANDO   ");
			HAL_GPIO_WritePin(BYPASS_GPIO_Port, BYPASS_Pin, 0);



		}

		if (selecao == 4) {
			if (run == 0) {
				lcd_goto(0x80);
				lcd_puts("   DESLIGADO :)  ");
			}

		} else
			__NOP();


		if (selecao == 5) {

			selecao = 1;
		} else
			__NOP();


		if(flag_sobrecorrente == 1)
													{
							HAL_GPIO_WritePin(BYPASS_GPIO_Port, BYPASS_Pin, 0);
												HAL_TIM_Base_Stop_IT(&htim1);
												HAL_TIM_Base_Stop_IT(&htim2);
											    HAL_TIM_Base_Stop_IT(&htim4);
											    TIM1->CNT = 0;
											    TIM2->CNT = 0;
											    TIM4->CNT = 0;
											    lcd_goto(0x80);
												lcd_puts("   REINICIE     ");
												lcd_goto(0xc0);
				       							lcd_puts("    O ARM       ");
				       							HAL_GPIO_WritePin(RedLed_GPIO_Port,RedLed_Pin,1);
													}


	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 3842;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 180;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 70;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 160;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 482;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 482;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 835;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 835;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 41999;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 9999;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, PPM_OUT_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, BYPASS_Pin|RedLed_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D6_Pin|D7_Pin|LCD_EN_Pin|D4_Pin 
                          |D5_Pin|LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ZCD_Pin */
  GPIO_InitStruct.Pin = ZCD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ZCD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : INCREMENTA_Pin */
  GPIO_InitStruct.Pin = INCREMENTA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(INCREMENTA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PPM_OUT_Pin LD2_Pin */
  GPIO_InitStruct.Pin = PPM_OUT_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BYPASS_Pin RedLed_Pin */
  GPIO_InitStruct.Pin = BYPASS_Pin|RedLed_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : D6_Pin D7_Pin LCD_EN_Pin D4_Pin 
                           D5_Pin LCD_RS_Pin */
  GPIO_InitStruct.Pin = D6_Pin|D7_Pin|LCD_EN_Pin|D4_Pin 
                          |D5_Pin|LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SOBRECORRENTE_Pin */
  GPIO_InitStruct.Pin = SOBRECORRENTE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(SOBRECORRENTE_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	if (htim->Instance == TIM3) {

		//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

		if (start == 1 && run == 0) {

			x++;

			soft = 1;

			if (x == CNTstart) {

				x = 0;
				PPM--;

				if (PPM >= 27) {

					TIM1->ARR = PPM;
				} else if(PPM<27) {
					run = 1;
					start = 0;
//					soft = 1;
					HAL_TIM_Base_Stop_IT(&htim3);
				}

				rPPM = PPM - 20;

				segundosreal = rtimes * rPPM;


			}
		}

		if (stop == 1 && run == 1) {

			x++;

			soft = 1;

			if (x == CNTstop) {

				x = 0;
				PPM++;

				if (PPM <= 189) {
					TIM1->ARR = PPM;
				} else {
					run = 0;
					soft = 0;
					HAL_TIM_Base_Stop_IT(&htim3);
				}
			}

			rPPM = PPM;
			rPPM = 200 - rPPM;

			segundosreal = rtimep * rPPM;

		}

	}

	if ((htim->Instance == TIM1) && (soft == 1)) {

		//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		HAL_GPIO_WritePin(GPIOA, PPM_OUT_Pin, 1);
		TIM2->CNT = 0;
		HAL_TIM_Base_Stop_IT(&htim1);
		HAL_TIM_Base_Start_IT(&htim2);

	}

	if (htim->Instance == TIM2) {

		HAL_GPIO_WritePin(GPIOA, PPM_OUT_Pin, 0);
		HAL_TIM_Base_Stop_IT(&htim2);

	}

	if ((htim->Instance == TIM4) && (fZCD == 1)) {
		fZCD = 0;
		HAL_TIM_Base_Stop_IT(&htim4);
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

//TESTA SE O BOTAO DE SELECAO FOI APERTADO
	if (repique && ((GPIOC->IDR & 0x2000) == 0) && flag_sobrecorrente==0) {

		selecao++;
		preselecao = 1;
		repique = 0;

	} else
		__NOP();

//TESTA SE O BOTAO DE INCREMENTO FOI APERTADO
	if (repique2  && ((GPIOA->IDR & 0x01) == 1) && flag_sobrecorrente==0) {

		incrementa = 1;
		repique2 = 0;

	} else
		__NOP();

	if (ZCD_Pin && (fZCD == 0) && flag_sobrecorrente==0) {
		fZCD = 1;
		TIM1->CNT = 0;
		HAL_TIM_Base_Start_IT(&htim1);
		HAL_TIM_Base_Start_IT(&htim4);
		TIM4->CNT = 0;

	} else
		__NOP();

	if(GPIO_Pin == SOBRECORRENTE_Pin )
	{


	if(preflag==1)
			{
				flag_sobrecorrente=1;


		}// else flag_sobrecorrente=0;
		//lcd_goto(0x80);
		//lcd_puts("   REINICIE    ");
		/*lcd_goto(0xc0);
		lcd_puts("    O ARM      ");
		HAL_TIM_Base_Stop_IT(&htim1);
		HAL_TIM_Base_Stop_IT(&htim2);
		HAL_TIM_Base_Stop_IT(&htim3);
	    HAL_TIM_Base_Stop_IT(&htim4);
	    TIM1->CNT = 0;
	    TIM2->CNT = 0;
	    TIM3->CNT = 0;
	    TIM4->CNT = 0;*/
	} else
		__NOP();
}

int i=0,  var=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

		HAL_UART_Receive_IT(&huart2,Data,4);
		i++;

					if(Data[0]=='t' && Data[1]=='s' )
					{
						ts_dez = (Data[2] - 48 )* 10;
						ts_un  = (Data[3] - 48 );

					}

					if(Data[0]=='t' && Data[1]=='d' )
					{
						td_dez = (Data[2] - 48 )* 10;
						td_un  = (Data[3] - 48 );

					}

					if(Data[0]=='i' && Data[1]=='n' )
					{
						selecao=3;
						preselecao=1;

					}

					if(Data[0]=='o' && Data[1]=='u' )
					{
						selecao=4;
						preselecao=1;

					}

					if(Data[0]=='r' && Data[1]=='e' )
					{
						selecao=5;

					}

					if(Data[0]=='d' && Data[1]=='c' )
					{
						selecao=2;

					}

					if(Data[0]=='d' && Data[1]=='1' )
					{
						selecao=1;

					}


											if(ts_time<5) ts_time = 5;
											if(td_time<5) td_time = 5;
											ts_time = ts_dez + ts_un;
											td_time = td_dez + td_un;
											segundostart = ts_time;
											segundostop = td_time;

											Data[0]=0;
											Data[1]=0;
											Data[2]=0;
											Data[3]=0;




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
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
