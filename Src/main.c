/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "assignment.h"
#include <stdbool.h>



int main(void)
{
  /*
   *  DO NOT WRITE TO THE WHOLE REGISTER!!!
   *  Write to the bits, that are meant for change.
   */


  /*
   * TASK - configure MCU peripherals so that button state can be read and LED will blink.
   * Button must be connected to the GPIO port A and its pin 3.
   * LED must be connected to the GPIO port A and its pin 4.
   *
   * In header file "assignment.h" define macros for MCU registers access and LED blink application.
   * Code in this file must use these macros for the peripherals setup.
   * Code of the LED blink application is already given so just the macros used in the application must be defined.
   */


  /* Enable clock for GPIO port A*/

	//type your code for GPIOA clock enable here:
	*((volatile uint32_t *) (uint32_t)(RCC_BASE_ADDR + RCC_AHBENR_REG)) |= (uint32_t)(1 << 17);

  /* GPIOA pin 3 and 4 setup */
	// Set mode for GPIOA pin 3
		*((volatile uint32_t *)((uint32_t)GPIOA_BASE_ADDR)) &= ~(uint32_t)(0x3 << 8);
	// Set mode for GPIOA pin 4
		*((volatile uint32_t *)((uint32_t)GPIOA_BASE_ADDR)) |= (uint32_t)(1 << 10);

	//type your code for GPIOA pins setup here:
	// OTYPER
		*((volatile uint32_t *)((uint32_t)(GPIOA_BASE_ADDR + GPIOA_OTYPER_REG))) &= ~(1 << 5);
	// OSPEEDR for GPIOA pin 4
		*((volatile uint32_t *)((uint32_t)(GPIOA_BASE_ADDR + GPIOA_OSPEEDER_REG))) &= ~(0x3 << 10);

	// GPIO PUPDR register, reset
	// Pull-up for GPIOA 3
		*((volatile uint32_t *)((uint32_t)(GPIOA_BASE_ADDR + GPIOA_PUPDR_REG))) |= (1 << 8);
	// No pull-up, pull-down for GPIOA 4
		*((volatile uint32_t *)((uint32_t)(GPIOA_BASE_ADDR + GPIOA_PUPDR_REG))) &= ~(0x3 << 10);

	//	uint8_t button;
	//	EDGE_TYPE edgeMain;


  while (1)
  {


	 /*if(BUTTON_GET_STATE)
	  {
		  // 0.25s delay
		  for(uint16_t i = 0; i < 0xFF00; i++){}
		  LED_ON;
		  // 0.25s delay
		  for(uint16_t i = 0; i < 0xFF00; i++){}
		  LED_OFF;
	  }
	  else
	  {
		  // 1s delay
		  for(uint32_t i = 0; i < 0xFFFF0; i++){}
		  LED_ON;
		  // 1s delay
		  for(uint32_t i = 0; i < 0xFFFF0; i++){}
		  LED_OFF;
	  }*/

	  //button = BUTTON_GET_STATE;
	  //edgeMain = edgeDetect(button,5);

  }

}

/* USER CODE BEGIN 4 */
static EDGE_TYPE edgeDetect(uint8_t pin_state, uint8_t samples)
{
	static uint8_t pin_state_before;
	static EDGE_TYPE edge;
	static int toggle;
	static bool toggle_initialized;

	  if (!toggle_initialized)
	  {
		  toggle = 1;
		  toggle_initialized = true;
		  pin_state_before=pin_state;
		  edge = NONE;
		  return edge;
	  }


	if(toggle)
			{

			if(pin_state_before!=pin_state)
				{
					if((pin_state==0) && (pin_state_before==16)&& ((edge==NONE)||(edge==RISE)))
					{
						edge=FALL;
						toggle=1;
						pin_state_before=pin_state;
					}
					else if((pin_state==16) && (pin_state_before==0)&& ((edge==NONE)||(edge==FALL)))
					{
						edge=RISE;
						toggle=1;
						pin_state_before=pin_state;
					}
				}
			else
				{
				toggle++;

				if((toggle>samples))
					{
					return edge;
					}
				}
			}

	return NONE;

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
