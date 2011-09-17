#include "LPD8806.h"
#include <pins_arduino.h>
#include <SPI.h>

/* Example to control LPD8806-based RGB LED Strips
 *****************************************************************************
 * Original code by Adafruit - MIT license
 * Pixel array, bit-shifting, and SPI (SPDR) calls based on WS2801
 *	modifications made by ph1x3r (ph1x3r@gmail.com)
 * Changes made by cjbaar (gth@cjbaar.com) to use SPI bus for communication
 *****************************************************************************
*/


/* initalize the library */

LPD8806::LPD8806(uint16_t n) {
	numLEDs = n;

	// malloc per pixel so we dont have to hardcode the length
	pixels = (uint32_t *)malloc(numLEDs);
}


/* setup a strip instance of n pixel length */

void LPD8806::begin(void) {
	// initialize the SPI bus
	// the strip uses default settings (mode=0, msbfirst), so we don't need to override anything
	SPI.begin();
	
	// run the SPI bus as fast as possible
	// this has been tested on a 16MHz Arduino Uno
	SPI.setClockDivider(SPI_CLOCK_DIV2);


	// clear the strip on startup
	// remember, even if we reset the controller, the LPD8806 chips hold state until told otherwise
	clear();
}


/* recall the number of pixels */

uint16_t LPD8806::numPixels(void) {
	return numLEDs;
}


/* create a 3-byte color string from individual r,g,b values */

uint32_t LPD8806::Color(byte r, byte g, byte b) {
	//Take the lowest 7 bits of each value and append them end to end
	// We have the top bit set high (its a 'parity-like' bit in the protocol
	// and must be set!)
	
	// (the LPD8806 wants the order to be green, red, blue)

	uint32_t x;
	x = g | 0x80;
	x <<= 8;
	x |= r | 0x80;
	x <<= 8;
	x |= b | 0x80;

	return(x);
}


/* Basic, push SPI data out */

void LPD8806::write8(uint8_t d) {
	// as noted by ph1x3r: Same as SPI.transfer(), but saves a call
	SPDR = d & 0xff;
	while (!(SPSR & (1<<SPIF))) {};
}


/* per Adafruit: */
// This is how data is pushed to the strip. 
// Unfortunately, the company that makes the chip didnt release the 
// protocol document or you need to sign an NDA or something stupid
// like that, but we reverse engineered this from a strip
// controller and it seems to work very nicely!

void LPD8806::show(void) {
	uint16_t i;
	
	// get the strip's attention
	write8(0);
	write8(0);
	write8(0);
	write8(0);

	// write 24 bits per pixel
	// LPD8806 order is g,r,b
	for (i=0; i<numLEDs; i++ ) {
    	write8(pixels[i]>>16 & 0xff);
    	write8(pixels[i]>>8 & 0xff);
    	write8(pixels[i] & 0xff);
	}
	
	// to 'latch' the data, we send just zeros
	//
	// original code wrote a ton of zeroes to latch (for 5m, 160*2*3=960 bytes)
	//for (i=0; i < (numLEDs*2); i++ ) {
	//	write8(0); 
	//	write8(0); 
	//	write8(0);		 
	//}
	//
	// in my testing, I have had no trouble latching with only a few zeroes being sent
	// if you experience issues, you may want to go back to the above code, and
	// I'd be interested to know if you run into issues with this
	write8(0);
	write8(0);
	write8(0);
	write8(0);
	
	
	// we need to have a delay here, 10ms seems to do the job
	// shorter may be OK as well - need to experiment :(
	
	// also seem to have no problems with a smaller delay
	delay(2);
}


/* reset the strip (write all black) */

void LPD8806::clear() {
	for (uint16_t i=0; i < numLEDs; i++) {
		setPixelColor(i, 0, 0, 0);
	}
	show();
}


/* store an rgb component in our array */

void LPD8806::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
    uint32_t data;
    if (n > numLEDs) return;

    data = (g | 0x80);
    data <<= 8;
    data |= (r | 0x80);
    data <<= 8;
    data |= (b | 0x80);

    pixels[n] = data;
}


/* store a 3-byte color component in our array */

void LPD8806::setPixelColor(uint16_t n, uint32_t c) {
    uint32_t data;
    if (n > numLEDs) return;

    data = ((c>>16) | 0x80);
    data <<= 8;
    data |= ((c>>8) | 0x80);
    data <<= 8;
    data |= ((c) | 0x80);

    pixels[n] = data;
}
