#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef unsigned short u16;
typedef unsigned char u8;

enum ECmdCode {
    CMD_NONE        = 0,    // 空指令
    CMD_CTL_SPEED   = 1,    // 设置小车速度
};

struct CmdHead {
    u16 size;    // 整个指令包长度
    u8 code;     // 指令代码
    u8 param;    // 参数
};

struct CmdTail {
    u16 sum;     // 校验和
};

class CmdBuf {
private:
    enum {
        BUFSIZE = 512
    };
    CmdHead* m_cmdHead;
    CmdTail* m_cmdTail;
    char m_buf[BUFSIZE];

private:
    int capacity();     // 能发送数据的容量

public:
    /*-------------------------用于构造指令包--------------------------*/
    CmdBuf();
    CmdBuf(u8 code, u8 param, char* buf, int size);
    u16 cmdSize();                          // 指令包大小
    void setCmdCode(u8 code);               // 设置code
    void setCmdParam(u8 param);             // 设置param
    bool setDatabuf(char* buf, int len);    // 设置数据缓冲区
    char* cmdBuf();                         // 获取指令缓冲区地址

    /*-------------------------用于解析指令包--------------------------*/
    CmdBuf(char* buf, int size);
    void setCmdBuf(char* buf, int size);
    u8 cmdCode();
    u8 cmdParam();
    u16 dataSize();             // 收到数据大小
    char* dataBuf();            // 数据缓冲区地址
};

#endif // PROTOCOL_H
