#include "ws2812.h"
#include "string.h"

static uint8_t ws2812_tx_buf[WS2812_NUM * 24];
static RGB_t pixel_buf[WS2812_NUM];

void WS2812_colorSet(uint8_t index, uint8_t R, uint8_t G, uint8_t B)
{
    if(index >= WS2812_NUM) return;
    pixel_buf[index].R = R;
    pixel_buf[index].G = G;
    pixel_buf[index].B = B;
}

void WS2812_Refresh(void)
{
    uint8_t i,j;
    uint8_t color;
    uint16_t pos = 0;

    for(i = 0; i < WS2812_NUM; i++)
    {
        // WS2812 顺序 GRB
        color = pixel_buf[i].G;
        for(j = 0; j < 8; j++)
        {
            ws2812_tx_buf[pos++] = (color & (0x80 >> j)) ? CODE_1 : CODE_0;
        }
        color = pixel_buf[i].R;
        for(j = 0; j < 8; j++)
        {
            ws2812_tx_buf[pos++] = (color & (0x80 >> j)) ? CODE_1 : CODE_0;
        }
        color = pixel_buf[i].B;
        for(j = 0; j < 8; j++)
        {
            ws2812_tx_buf[pos++] = (color & (0x80 >> j)) ? CODE_1 : CODE_0;
        }
    }

    while(WS2812_SPI_HANDLE.State == HAL_SPI_STATE_BUSY_TX);
    HAL_SPI_Transmit(&WS2812_SPI_HANDLE, ws2812_tx_buf, sizeof(ws2812_tx_buf), 10000);
    while(WS2812_SPI_HANDLE.State == HAL_SPI_STATE_BUSY_TX);
    HAL_Delay(1);
}

void WS2812_Clear(void)
{
    memset(pixel_buf, 0, sizeof(pixel_buf));
    WS2812_Refresh();
}
