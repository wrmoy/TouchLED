/*
 * adc.h
 * ADC header file, includes ADC function declarations and enum definitions
 * by William Moy
 */

#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

// ADC prescaler options: select a F_cpu clock divider
#define ADC_CLK_DIV_MASK    0b00000111
#define ADC_CLK_DIV_2       0b00000001
#define ADC_CLK_DIV_4       0b00000010
#define ADC_CLK_DIV_8       0b00000011
#define ADC_CLK_DIV_16      0b00000100
#define ADC_CLK_DIV_32      0b00000101
#define ADC_CLK_DIV_64      0b00000110
#define ADC_CLK_DIV_128     0b00000111

// ADC output result alignment options
#define ADC_ALIGN_MASK      0b00010000
#define ADC_RIGHT_ALIGN     0b00000000
#define ADC_LEFT_ALIGN      0b00010000

#define ADC_CHANNEL_MASK    0b00011111
#define ADC0_SINGLE         0b00000000
#define ADC1_SINGLE         0b00000001
#define ADC2_SINGLE         0b00000010
#define ADC3_SINGLE         0b00000011
#define ADC4_SINGLE         0b00000100
#define ADC5_SINGLE         0b00000101
#define ADC6_SINGLE         0b00000110
#define ADC7_SINGLE         0b00000111


void adc_init(void);
void adc_set_prescaler(uint8_t);
void adc_set_align(uint8_t);
void adc_select(uint8_t);
void adc_enable_int(void);
void adc_disable_int(void);
uint16_t adc_get_value16(void);
uint8_t adc_get_value8(void);
void adc_start(void);
void adc_clear_flag(void);
uint8_t adc_is_running(void);


#endif
