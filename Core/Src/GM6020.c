//
// Created by Redmi on 2026/11/16.
//
#include "main.h" // 调用底层 CAN 发送函数
#include "bsp_can.h"
#include "GM6020.h"

/**
 * @brief 控制 ID1~4 的四个 GM6020 电机 (电流控制模式)
 * @param cur1~cur4 对应 ID 1~4 的电流给定值 (-16384 ~ 16384)
 */
void GM6020Move(int16_t cur1, int16_t cur2, int16_t cur3, int16_t cur4)
{
    uint8_t data[8];

    // 1. 限幅    -16384 ~ 16384
    if (cur1 >  16384) cur1 =  16384;
    if (cur1 < -16384) cur1 = -16384;
    if (cur2 >  16384) cur2 =  16384;
    if (cur2 < -16384) cur2 = -16384;
    if (cur3 >  16384) cur3 =  16384;
    if (cur3 < -16384) cur3 = -16384;
    if (cur4 >  16384) cur4 =  16384;
    if (cur4 < -16384) cur4 = -16384;

    // 2. 拆分大小部分数据
    // 电机 1
    data[0] = (cur1 >> 8) & 0xFF;
    data[1] =  cur1       & 0xFF;

    // 电机 2
    data[2] = (cur2 >> 8) & 0xFF;
    data[3] =  cur2       & 0xFF;

    // 电机 3
    data[4] = (cur3 >> 8) & 0xFF;
    data[5] =  cur3       & 0xFF;

    // 电机 4
    data[6] = (cur4 >> 8) & 0xFF;
    data[7] =  cur4       & 0xFF;

    // 3. 调用发送函数
    fdcanx_send_data(&hfdcan1, 0x1FE, data, 8);

}