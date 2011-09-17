#include <WProgram.h>
#include <SPI.h>

class LPD8806 {
 private:
  void write8(byte);
  // the arrays of bytes that hold each LED's 24 bit color values
  uint32_t * pixels;
  uint16_t numLEDs;

 public:
  LPD8806(uint16_t n);
  void begin();
  void show();
  void clear();
  void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
  void setPixelColor(uint16_t n, uint32_t c);
  uint16_t numPixels(void);
  uint32_t Color(byte, byte, byte);
};
