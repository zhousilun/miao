//
// Created by Redmi on 2026/10/15.
//

#ifndef PRO10_13_1_PID_H
#define PRO10_13_1_PID_H
extern float Kp, Ki, Kd;       //参数初始化
extern float pid_internal;

void pidInit(float kp,float ki,float kd,float currVal,float target);
int pid_calc(float);


#endif //PRO10_13_1_PID_H
