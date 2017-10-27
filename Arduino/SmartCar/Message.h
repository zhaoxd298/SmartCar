#ifndef MESSAGE_H
#define MESSAGE_H

#include "Motor.h"

void initSerail();
bool getDataUpdateFlg();
void clearDataUpdateFlg();
bool getCtlParam(CtlParam& param);


#endif