This is a fork of an Arduino library for LPD8806 PWM LED driver chips, strips and pixels
(See: git://github.com/adafruit/LPD8806 for original)

Pick some up LED pixel strips at http://www.adafruit.com/products/306

Be sure to review the tutorial and power requirements at http://www.ladyada.net/products/digitalrgbledstrip/index.html -- don't power the strip from your Arduino!


CHANGES

This version of the code has been modified to utilize the SPI bus for much faster communication. Since it takes advantage of SPI hardware in the chipset, I have achieved a speed increase of up to 34x over the original software method.

Some SPI and pixel-storage modifications were sourced from the modified WS2801-Library by ph1x3r.

This library has been tested running at up to 1/2 clock speed on a 16MHz Arduino Uno. It uses MOSI (Uno=11, Mega=51) for the data, and SCK (Uno=13, Mega=52) for clock. The SS pin (Uno=10, Mega=53) is not utilized, but keep in mind it must be kept reserved as an output, otherwise the Arduino may jump into SPI slave mode.

Based on the wiring in the tutorial above, the yellow wire (CI) will go to the SCK pin, and the green wire (DI) will go to the MOSI pin.

There is no SS/CS on these strips, so it may not be compatible if you have other SPI devices running at the same time. It may be possible to create your own CS effect by blocking the MOSI and SCK lines with transistors, but I haven't tested this to see if they can keep up with the 8MHz refresh rate.


INSTALLING

To download. click the DOWNLOADS button in the top right corner, rename the uncompressed folder LPD8806. Check that the LPD8806 folder contains LPD8806.cpp and LPD8806.h

Place the LPD8806 library folder your <arduinosketchfolder>/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.


PS

These strips are awesome.
