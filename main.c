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
#include "suart.h"

#define LED_TOP                 0   // port A, pin 13 on attiny84
#define LED_BOTTOM              2   // port A, pin 11 on attiny84
#define LIGHT_THRESHOLD         128 // arbitrary value, untested

int main(void) {
    // LED on or off flag
    uint8_t isDark = 0;

    /* Initialize LED */
    bit_set(DDRA, LED_TOP);
    bit_set(DDRA, LED_BOTTOM);

    /* Initialize ADC */
    adc_init();
    adc_set_prescaler(ADC_CLK_DIV_2);
    adc_set_align(ADC_LEFT_ALIGN);
    adc_select(ADC0_SINGLE);

    /* Initialize SUART */
    suart_init();

    while (1) {
        /* Emit light */
        bit_set(DDRA, LED_TOP); // set as output
        bit_clear(PORTA, LED_TOP);
        bit_set(PORTA, LED_BOTTOM);
        if (isDark) {
            _delay_ms(10);
            bit_clear(PORTA, LED_BOTTOM);
            _delay_ms(190);
        }
        else {
            _delay_ms(200);
        }
        /* Reverse bias */
        bit_set(PORTA, LED_TOP);
        bit_clear(PORTA, LED_BOTTOM);
        /* Discharge and measure */
        bit_clear(DDRA, LED_TOP); // set as input, change to ADC
        adc_start();
        while (adc_is_running())
            ;
        uint8_t val = adc_get_value8();
        if (val > LIGHT_THRESHOLD)
            isDark = 1;
        else
            isDark = 0;
        suart_xmit(val);
        _delay_ms(800);
    }

    return 0;
}

