#include "Protocol.h"
#include <Arduino.h>
#include <stdlib.h>

CmdBuf::CmdBuf()
{
    m_cmdHead = reinterpret_cast<CmdHead*>(m_buf);

    m_cmdHead->size = sizeof(CmdHead) + sizeof(CmdTail);
    m_cmdHead->code = CMD_NONE;
    m_cmdHead->param = 0;

    m_cmdTail = reinterpret_cast<CmdTail*>(m_buf + m_cmdHead->size);

    m_cmdTail->sum = 0;
}

CmdBuf::CmdBuf(u8 code, u8 param, char* buf, int size)
{
    if (size > capacity()) {
        size = capacity();
    }

    m_cmdHead = reinterpret_cast<CmdHead*>(m_buf);

    m_cmdHead->size = static_cast<u16>(sizeof(CmdHead) + sizeof(CmdTail) + size);


    m_cmdHead->code = code;
    m_cmdHead->param = param;



    m_cmdTail = reinterpret_cast<CmdTail*>(m_buf + m_cmdHead->size);

    m_cmdTail->sum = 0;

    if (NULL != buf) {
        memcpy(m_buf+sizeof(CmdHead), buf, size);
    }
}

u16 CmdBuf::cmdSize()
{
    return m_cmdHead->size;
}

void CmdBuf::setCmdCode(u8 code)
{
    m_cmdHead->code = code;
}

void CmdBuf::setCmdParam(u8 param)
{
    m_cmdHead->param = param;
}

bool CmdBuf::setDatabuf(char* buf, int len)
{
    if (len > capacity()) {
        len = capacity();
    }

    m_cmdHead->size = sizeof(CmdHead) + sizeof(CmdTail) + len;

    m_cmdTail = reinterpret_cast<CmdTail*>(m_buf + m_cmdHead->size);

    m_cmdTail->sum = 0;

    if (NULL != buf) {
        memcpy(m_buf+sizeof(CmdHead), buf, len);
    }

    return true;
}

char* CmdBuf::cmdBuf()
{
    return m_buf;
}


CmdBuf::CmdBuf(char* buf, int size)
{
    setCmdBuf(buf, size);
}

void CmdBuf::setCmdBuf(char* buf, int size)
{
    if ((NULL != buf) || (size > 0)) {
        if (size > BUFSIZE) {
            size = BUFSIZE;
        }
        memcpy(m_buf, buf, size);
    }

    m_cmdHead = reinterpret_cast<CmdHead*>(m_buf);

    m_cmdTail = reinterpret_cast<CmdTail*>(m_buf + m_cmdHead->size);
}

u8 CmdBuf::cmdCode()
{
    return (m_cmdHead->code);
}

u8 CmdBuf::cmdParam()
{
    return (m_cmdHead->param);
}

u16 CmdBuf::dataSize()
{
    return (m_cmdHead->size - sizeof(CmdHead) - sizeof(CmdTail));
}

char* CmdBuf::dataBuf()
{
    return (m_buf + sizeof(CmdHead));
}


int CmdBuf::capacity()
{
    return (BUFSIZE - sizeof(CmdHead) - sizeof(CmdTail));
}
