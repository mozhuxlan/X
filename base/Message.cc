#include "Message.h"

CMessage::CMessage(int src, int dst, const char *str, int sz)
{
	m_src = src;
	m_dst = dst;
	m_buf.Push(str, sz);
}

CMessage::~CMessage()
{
}

CMessage::CMessage(const CMessage &rhs)
{
	m_src = rhs.m_src;
	m_dst = rhs.m_dst;
	m_buf = rhs.m_buf;
}

CMessage &CMessage::operator=(const CMessage &rhs)
{
	if(&rhs == this)
	{
		return *this;
	}
	m_src = rhs.m_src;
	m_dst = rhs.m_dst;
	m_buf = rhs.m_buf;
	return *this;
}
