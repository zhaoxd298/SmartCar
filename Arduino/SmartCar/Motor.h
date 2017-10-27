#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

struct CtlParam {
    bool direction;
    int speed;
    int angle;
};

class Motor {
private:
    enum {
        LEFT_MOTOR_FORWARD_PIN  = 3,    // 控制左轮正转
        LEFT_MOTOR_BACK_PIN     = 9,    // 控制左轮反转
        
        RIGHT_MOTOR_FORWARD_PIN = 10,   // 控制右轮正转
        RIGHT_MOTOR_BACK_PIN    = 11,   // 控制右轮反转
    };

public:
    Motor();
    ~Motor();

    /**
    *  控制小车前进
    * @angle：小车前进的角度(偏离直行的角度)，负数表示左转，正数表示右转
    * @speed:速度
    */
    void ctlCarGoForward(int angle, int speed); 
    /**
    *  控制小车倒退
    * @angle：小车倒退的角度，负数表示左转，正数表示右转
    * @speed:速度
    */   
    void ctlCarGoBack(int angle, int speed);

    void ctlCar(CtlParam& param);
};


#endif