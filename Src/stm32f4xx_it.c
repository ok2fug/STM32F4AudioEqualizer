#include "main.h"
#include "stm32f4xx_it.h"
#include "arm_math.h"
#include "filter.h"

extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim6;
extern ADC_HandleTypeDef hadc1;

void NMI_Handler(void) {
}

void HardFault_Handler(void) {
	while (1) {
	}
}

void MemManage_Handler(void) {
	while (1) {
	}
}

void BusFault_Handler(void) {
	while (1) {
	}
}

void UsageFault_Handler(void) {
	while (1) {
	}
}

void SVC_Handler(void) {
}

void DebugMon_Handler(void) {
}

void PendSV_Handler(void) {
}

void SysTick_Handler(void) {
	HAL_IncTick();
}

void TIM6_DAC_IRQHandler(void) {

	/*
	uint32_t adcSample;

	if (HAL_ADC_PollForConversion(&hadc1, 500) == HAL_OK){
		adcSample = HAL_ADC_GetValue(&hadc1);
		insertInputStreamSample((uint32_t *)&adcSample);
	}
	 */

	insertInputStreamSampleMock();

	// Escribo una muestra del buffer de salida al DAC
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 2048 + (int32_t)*getOutputStreamSample());

	HAL_DAC_IRQHandler(&hdac);
	HAL_TIM_IRQHandler(&htim6);
}

