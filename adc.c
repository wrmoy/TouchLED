/*
 * adc.c
 * Analog-to-digital conversion functions.  Option setters and value getters
 * are abound.
 * by William Moy
 */

#include <avr/io.h>
#include "adc.h"
#include "common.h"

/** 
 * adc_init
 * Enables the ADC hardware
 * args:
 *  none
 * returns:
 *  none
 */
void adc_init(void) {
    bit_set(ADCSRA, ADEN);
}

/** 
 * adc_set_prescaler
 * Set the clock speed divider input to the ADC clock.
 * args:
 *  prescaler: enum value defined in ADC_PRESCALER_OPTIONS
 * returns:
 *  none
 */
void adc_set_prescaler(uint8_t prescaler) {
    ADCSRA &= ~(ADC_CLK_DIV_MASK); // Zero out the biis 0-2
    ADCSRA |= prescaler;
}

/** 
 * adc_set_align
 * Set the bit alignment of the ADC output.  If ADC_LEFT_ALIGN is set, then
 * MSB of result will be at ADCH[7] and LSB at ADCL[6].  If ADC_RIGHT_ALIGN is
 * set, then MSB of result will be at ADCH[1] and LSB at ADCL[0].
 * args:
 *  alignOption: enum value defined in ADC_ALIGN_OPTIONS
 * returns:
 *  none
 */
void adc_set_align(uint8_t alignOption) {
    ADCSRB &= ~(ADC_ALIGN_MASK);
    ADCSRB |= alignOption;
}

/** 
 * adc_select
 * Select the input channel or differential channels to be sent to the
 * converter.  WARNING: NOT ALL INPUT OPTIONS ARE IMPLEMENTED!
 * args:
 *  inputOption: enum value defined in ADC_CHANNEL_OPTIONS
 * returns:
 *  none
 */
void adc_select(uint8_t inputOption) {
    ADMUX &= ~(ADC_CHANNEL_MASK); // Zero out the bits 0-5
    ADMUX |= inputOption;
    
}

/** 
 * adc_enable_int
 * Enable interrupts for the ADC.  An interrupt will be thrown when a
 * conversion is complete.
 * args:
 *  none
 * returns:
 *  none
 */
void adc_enable_int(void) {
    bit_set(ADCSRA, ADIE);
}

/** 
 * adc_enable_int
 * Disables interrupts for the ADC.
 * args:
 *  none
 * returns:
 *  none
 */
void adc_disable_int(void) {
    bit_clear(ADCSRA, ADIE);
}

/** 
 * adc_get_value16
 * Gets the conversion result in a 16-bit uint16_t.
 * args:
 *  none
 * returns:
 *  uint16_t: ADC conversion result
 */
uint16_t adc_get_value16(void) {
    if (bit_is_clear(ADCSRB, ADLAR))
        return ADC;
    else
        return ADC >> 6;
}

/** 
 * adc_get_value8
 * Get the truncated conversion results in 8-bit uint8_t (actual results are
 * 10-bits)
 * args:
 *  none
 * returns:
 *  uint8_t: ADC conversion result
 */
uint8_t adc_get_value8(void) {
    if (bit_is_set(ADCSRB, ADLAR))
        return ADCH;
    else
        return (ADCL >> 2) & (ADCH << 6);
}

/** 
 * adc_start
 * Starts an analog-to-digital conversion based on the current settings
 * args:
 *  none
 * returns:
 *  none
 */
void adc_start(void) {
    bit_set(ADCSRA, ADSC);
}

/** 
 * adc_clear_flag
 * Clears the flag that signals the end of a conversion.  This is unnecessary
 * if ADC interrupts are enabled and the ISR is called.
 * args:
 *  none
 * returns:
 *  none
 */
void adc_clear_flag(void) {
    bit_set(ADCSRA, ADIF);
}

/** 
 * adc_is_running
 * Checks if a conversion is currently running
 * args:
 *  none
 * returns:
 *  uint8_t: "true" is a conversion is running, "false" if not running
 */
uint8_t adc_is_running(void) {
    return bit_is_set(ADCSRA, ADSC);
}
