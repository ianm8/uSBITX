#ifndef UTIL_H
#define UTIL_H

#define CW_SIDETONE 700u

#define _rev2(x)  ((((x)&1)<<1) | (((x)>>1)&1))
#define _rev4(x)  ((_rev2(x)<<2) | (_rev2((x)>>2)))
#define _rev8(x)  ((_rev4(x)<<4) | (_rev4((x)>>4)))
#define _rev16(x) ((_rev8(x)<<8) | (_rev8((x)>>8)))

#define _rev(x) (uint16_t)(_rev16(x))

#define LCD_BLACK  _rev(TFT_BLACK)
#define LCD_WHITE  _rev(TFT_WHITE)
#define LCD_RED    _rev(TFT_RED)
#define LCD_GREEN  _rev(TFT_GREEN)
#define LCD_BLUE   _rev(TFT_BLUE)
#define LCD_YELLOW _rev(TFT_YELLOW)
#define LCD_PINK   _rev(TFT_PINK)
#define LCD_PURPLE _rev(TFT_PURPLE)
#define LCD_MODE   _rev(0xf000)
//#define LCD_MODE   _rev(0x0018)

#endif