//
// Created by Redmi on 2026/10/15.
//
#include "pid.h"
#include <stdio.h>


float pid_internal;
float target;
float cullVal;
void pidInit(float kp,float ki,float kd,float currVal,float target) {
    Kp = 18.0f;
    Ki = 0.2f;
    Kd = 0.4f;
}


int pid_calc(float target) {

    //part p
    ins_data_t *ins = ins_data();
    float error = ins->pitch - target;
    float p_out = Kp * error;



    //积分
    pid_internal += error;
    if (pid_internal > 220) {
        pid_internal = 220;
    }
    if (pid_internal < -220) {
        pid_internal = -220;
    }
    float i_out = Ki * pid_internal;


    //微分
    float d_out = -Kd * ins->gyro[1];




    int pwm = (int)(p_out + i_out + d_out);
    if (pwm>800) {
        pwm =800;
    }
    if (pwm<-800) {
        pwm = -800;
    }


    return pwm;
}


void pid_reset(void) {
    pid_internal = 0.0f;
}
