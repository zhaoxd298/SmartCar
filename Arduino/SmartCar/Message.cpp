#include "Message.h"
#include "Protocol.h"

#include <Arduino.h>

static bool dataUpdateFlg;      // 数据更新标志位

static bool recvFlg = NULL;     // 接收数据标志，只接收包头时为true，接收完时为false
static CmdBuf* cmd;          // 解析数据包类
static char buf[512];           // 全局缓冲区
static CmdHead* cmdHead = NULL;    
static int len = 0;

void initSerail()
{
    Serial.begin(115200);
    cmd = new CmdBuf();
    cmdHead = reinterpret_cast<CmdHead*>(buf);
}

void serialEvent()
{
    //memset(buf, 0, sizeof(buf));
    //len = Serial.available();
    if (false == recvFlg) {     // 当前缓冲区没有任何数据
        len = Serial.readBytes(buf, sizeof(CmdHead));
        recvFlg = true;
    } else {
        len += Serial.readBytes(buf+len, cmdHead->size-len);
        recvFlg = false;
        dataUpdateFlg = true;

        cmd->setCmdBuf(buf, len);

        //Serial.print("Serial read data size:");
        //Serial.println(len);
        //Serial.println(cmd->dataBuf());
    }

    // Serial.print("Serial read data size:");
    // Serial.println(len);
}


bool getDataUpdateFlg()
{
    return dataUpdateFlg;
}

void clearDataUpdateFlg()
{
    dataUpdateFlg = false;
}

bool getCtlParam(CtlParam& param)
{
    char* ptr = strtok(cmd->dataBuf(), "@#");

    if (0 != strcmp(ptr, "car")) {
        return false;
    }

    char* p;
	while (ptr != NULL) {  
        p = strstr(ptr, "=");
		if (NULL != p) {
            p ++;

            if (strstr(ptr, "dir")) {
                param.direction = atoi(p);
            } else if (strstr(ptr, "spd")) {
                param.speed = atoi(p);
            } else if (strstr(ptr, "ang")) {
                param.angle = atoi(p);
            }
        }

        ptr = strtok(NULL, "#");  
    }

    dataUpdateFlg = false;

    return true;
}
