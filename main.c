/*
 * TouchLED
 * by William Moy
 *
 * This should be a fairly simple project that demonstrates the use of
 * an LED as an emitter as well as a receiver.
 * Inspired by http://www.seanet.com/~karllunt/fireflyLED.html and
 * http://www.merl.com/publications/docs/TR2003-35.pdf
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "common.h"

#define LED_BIT                 1   // port A, pin 13 on attiny84
#define LIGHT_THRESHOLD         128 // arbitrary value, untested

int main(void) {
    // LED on or off flag
    uint8_t isDark = 0;

    /* Initialize LED */
    bit_set(DDRA, LED_BIT);
    /* Initialize ADC */
    adc_init();
    adc_set_prescaler(ADC_CLK_DIV_2);
    adc_set_align(ADC_LEFT_ALIGN);
    adc_select(ADC0_SINGLE);

    while (1) {
        bit_set(PORTA, LED_BIT);
        if (isDark)
            _delay_ms(10);
        else
            _delay_ms(200);
        bit_clear(PORTA, LED_BIT);
        bit_clear(DDRA, LED_BIT);
        adc_start();
        while (adc_is_running())
            ;
        if (adc_get_value8() > LIGHT_THRESHOLD)
            isDark = 1;
        else
            isDark = 0;
        _delay_ms(800);
    }

    return 0;
}

