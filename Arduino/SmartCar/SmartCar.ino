#include <Arduino.h>
#include "Message.h"
#include "Motor.h"

Motor motor;
CtlParam ctlParam;

void setup()
{
    initSerail();

    //motor.ctlCarGoForward(30);
    motor.ctlCarGoBack(0, 0);
}

void loop()
{
    if (getDataUpdateFlg()) {
        if (getCtlParam(ctlParam)) {
            motor.ctlCar(ctlParam);
        }
    }
}


