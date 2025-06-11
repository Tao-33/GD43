#ifndef __ADC_H
#define __ADC_H
#include "HeaderFiles.h"
extern uint16_t adc_value[2];
void ADC_Port_Init(void);
void ADC_Init(void);
void DMA_ADC_config_Init(void);

#endif

