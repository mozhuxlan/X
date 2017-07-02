#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "Buffer.h"
#include <iostream>

class CMessage
{
public:
	CMessage(int src, int dst, const char *str, int len);
	~CMessage();
	CMessage(const CMessage &rhs);
	CMessage& operator=(const CMessage &rhs);

private:
	int m_src;
	int m_dst;
	CBuffer m_buf;
};


#endif
