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
#define LIGHT_THRESHOLD         0x55 // arbitrary value, untested

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
        if (isDark) {
            bit_set(PORTA, LED_BOTTOM);
        }
        else {
            bit_clear(PORTA, LED_BOTTOM);
        }
        _delay_ms(2);
        /* Reverse bias */
        bit_set(PORTA, LED_TOP);
        bit_clear(PORTA, LED_BOTTOM);
        _delay_ms(1);
        /* Discharge and measure */
        bit_clear(PORTA, LED_TOP);
        bit_clear(DDRA, LED_TOP); // set as input, change to ADC
        uint8_t val = 1;
        uint16_t cnt = 0;
        while (val > 0){
            adc_start();
            while (adc_is_running())
                ;
            val = adc_get_value8();
            cnt++;
        }
        if (cnt > LIGHT_THRESHOLD)
            isDark = 1;
        else
            isDark = 0;
        // suart_xmit((uint8_t)(cnt>>8));
        // suart_xmit((uint8_t)(cnt));
        _delay_ms(8);
    }

    return 0;
}

