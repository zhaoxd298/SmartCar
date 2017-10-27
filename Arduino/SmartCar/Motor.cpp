#include "Motor.h"

Motor::Motor()
{
    pinMode(LEFT_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_BACK_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_BACK_PIN, OUTPUT);
}

Motor::~Motor()
{

}

void Motor::ctlCarGoForward(int angle, int speed)
{
    // 倒退PWM管脚输出低电平
    analogWrite(LEFT_MOTOR_BACK_PIN, 0);
    analogWrite(RIGHT_MOTOR_BACK_PIN, 0);

    if (speed < 0) {
        speed = 0;
    }
    
    if (speed > 255) {
        speed = 255;
    }

    int leftSpeed;
    int rightSpeed;

    if (0 == angle) {           // 直行   
        leftSpeed = speed;
        rightSpeed = speed;
    } else if (angle < 0) {     // 左转
        if (angle < -90) {
            angle = -90;
        }
        angle = -angle;
        angle = 90 - angle;
        leftSpeed = angle * speed / 90;
        rightSpeed = speed;

    } else if (angle > 0) {     // 右转
        if (angle > 90) {
            angle = 90;
        }
        angle = 90 - angle;
        rightSpeed = angle * speed / 90;
        leftSpeed = speed;
    }

    // Serial.print("angle:");
    // Serial.println(angle);
    // Serial.print("leftSpeed:");
    // Serial.println(leftSpeed);
    // Serial.print("rightSpeed:");
    // Serial.println(rightSpeed);

    analogWrite(LEFT_MOTOR_FORWARD_PIN, leftSpeed);
    analogWrite(RIGHT_MOTOR_FORWARD_PIN, rightSpeed);
}

void Motor::ctlCarGoBack(int angle, int speed)
{
    // 前进PWM管脚输出低电平
    analogWrite(LEFT_MOTOR_FORWARD_PIN, 0);
    analogWrite(RIGHT_MOTOR_FORWARD_PIN, 0);

    if (speed < 0) {
        speed = 0;
    }
    
    if (speed > 255) {
        speed = 255;
    }

    int leftSpeed;
    int rightSpeed;

    if (0 == angle) {           // 直行   
        leftSpeed = speed;
        rightSpeed = speed;
    } else if (angle < 0) {     // 左转
        if (angle < -90) {
            angle = -90;
        }
        angle = -angle;
        angle = 90 - angle;
        leftSpeed = angle * speed / 90;
        rightSpeed = speed;
    } else if (angle > 0) {     // 右转
        if (angle > 90) {
            angle = 90;
        }
        angle = 90 - angle;
        rightSpeed = angle * speed / 90;
        leftSpeed = speed;
    }

    analogWrite(LEFT_MOTOR_BACK_PIN, leftSpeed);
    analogWrite(RIGHT_MOTOR_BACK_PIN, rightSpeed);
}

void Motor::ctlCar(CtlParam& param)
{
    Serial.println("Motor::ctlCar");
    if (true == param.direction) {      // 前进
        ctlCarGoForward(param.angle, param.speed);
    } else {
        ctlCarGoBack(param.angle, param.speed);
    }
}