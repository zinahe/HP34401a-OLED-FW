/* Define to prevent recursive inclusion */
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "Adafruit_GFX.h"

/* Dimensions */
#define LCD_DIMENSION_X 256
#define LCD_DIMENSION_Y 64

/* Color definitions */
// 4 bit greyscale display
#define LCD_BLACK 0x0
#define LCD_DARK_GREY 0x3
#define LCD_GREY 0x7
#define LCD_LIGHT_GRAY 0xA
#define LCD_WHITE 0xF

// Control pins
#define LCD_RD_PORT GPIOB
#define LCD_RD_PIN 0
#define LCD_WR_PORT GPIOB
#define LCD_WR_PIN 1
#define LCD_RS_PORT GPIOB
#define LCD_RS_PIN 2
#define LCD_CS_PORT GPIOB
#define LCD_CS_PIN 11
#define LCD_RST_PORT GPIOB
#define LCD_RST_PIN 10
// Data pins are GPIOA[0-7]

#define PIN_LOW(port, pin) ((port)->regs->BRR = 1 << (pin))
#define PIN_HIGH(port, pin) ((port)->regs->BSRR = 1 << (pin))

#define RD_LOW PIN_LOW(LCD_RD_PORT, LCD_RD_PIN)
#define RD_HIGH PIN_HIGH(LCD_RD_PORT, LCD_RD_PIN)
#define WR_LOW PIN_LOW(LCD_WR_PORT, LCD_WR_PIN)
#define WR_HIGH PIN_HIGH(LCD_WR_PORT, LCD_WR_PIN)
#define CD_COMMAND PIN_LOW(LCD_RS_PORT, LCD_RS_PIN)
#define CD_DATA PIN_HIGH(LCD_RS_PORT, LCD_RS_PIN)
#define CS_ACTIVE PIN_LOW(LCD_CS_PORT, LCD_CS_PIN)
#define CS_IDLE PIN_HIGH(LCD_CS_PORT, LCD_CS_PIN)
#define RESET_ACTIVE PIN_LOW(LCD_RST_PORT, LCD_RST_PIN)
#define RESET_IDLE PIN_HIGH(LCD_RST_PORT, LCD_RST_PIN)

void displaySetup();

class Display : public Adafruit_GFX {
public:
  Display();
  void reset(void);
  void begin();
  virtual void drawPixel(int16_t x, int16_t y, uint16_t color);
  uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
  }
  void WriteCmdData(uint8_t cmd, uint16_t dat);
  virtual void setRotation(uint8_t r);
  virtual void invertDisplay(bool i);
  virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                        uint16_t color);
  virtual void fillScreen(uint16_t color) {
    fillRect(0, 0, _width, _height, color);
  }
  virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    fillRect(x, y, 1, h, color);
  }
  virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    fillRect(x, y, w, 1, color);
  }
  void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);
  void pushPixels(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *data, uint8_t c);
  virtual void startWrite(void);
  virtual void endWrite(void);

private:
  uint8_t rotation = 0;
};

#endif /* __DISPLAY_H */
