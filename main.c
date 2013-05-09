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

// initialize LED, ADC
// loop over:
//   set LED to high ("on" duty cycle)
//   wait for some time, depending on "visible" flag
//   set LED to low
//   set LED pin to ADC
//   pause?
//   grab an ADC sample
//   if it's below a certain threshold: (ambient light is bright)
//      set flag to indicate if LED should be visible
//   wait for some time ("off" duty cycle)
