#ifndef __WS2812_H
#define __WS2812_H

#include "main.h"
#include "spi.h"

#define WS2812_SPI_HANDLE    hspi6
#define WS2812_NUM           1    // 喵板板载1颗WS2812

#define CODE_0 0x03
#define CODE_1 0x3F

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGB_t;

void WS2812_colorSet(uint8_t index, uint8_t R, uint8_t G, uint8_t B);
void WS2812_Refresh(void);
void WS2812_Clear(void);

#endif