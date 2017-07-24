#include "buffer.h"
#include <string.h>
#include <stdlib.h>

CBuffer::CBuffer() : m_start(0), m_end(0), m_capacity(0), m_ptr(nullptr)
{
}

CBuffer::~CBuffer()
{
	if(m_ptr != nullptr)
	{
		delete []m_ptr;
	}
}

CBuffer::CBuffer(const CBuffer &rhs)
{
	m_ptr = new char[rhs.m_capacity];
	memcpy(m_ptr, rhs.m_ptr, rhs.m_capacity);
	m_start = rhs.m_start;
	m_end = rhs.m_end;
	m_capacity = rhs.m_capacity;
}

CBuffer &CBuffer::operator=(const CBuffer &rhs)
{
	if(this == &rhs)
	{
		return *this;
	}
	if(m_ptr != nullptr)
	{
		delete []m_ptr;
	}
	m_ptr = new char[rhs.m_capacity];
	memcpy(m_ptr, rhs.m_ptr, rhs.m_capacity);
	m_start = rhs.m_start;
	m_end = rhs.m_end;
	m_capacity = rhs.m_capacity;
	return *this;
}

CBuffer::CBuffer(CBuffer &&rhs)
{
	m_ptr = rhs.m_ptr;
	m_start = rhs.m_start;
	m_end = rhs.m_end;
	m_capacity = rhs.m_capacity;

	rhs.m_ptr = nullptr;
	rhs.m_start = 0;
	rhs.m_end = 0;
	rhs.m_capacity = 0;
}

CBuffer &CBuffer::operator=(CBuffer &&rhs)
{
	if(m_ptr != nullptr)
	{
		delete []m_ptr;
	}
	m_ptr = rhs.m_ptr;
	m_start = rhs.m_start;
	m_end = rhs.m_end;
	m_capacity = rhs.m_capacity;

	rhs.m_ptr = nullptr;
	rhs.m_start = 0;
	rhs.m_end = 0;
	rhs.m_capacity = 0;
	return *this;
}

void CBuffer::Add(const char *str, int len)
{
	if(m_capacity - m_end <= len)
	{
		Collect();
	}
	if(m_capacity - m_end <= len)
	{
		Expand((m_capacity + len) * 2);
	}
	memmove(m_ptr + m_end, str, len);
	m_end += len;
}

void CBuffer::Del(int len)
{
	m_start += len;
}

void CBuffer::Clear()
{
	m_start = m_end = 0;
}

const char *CBuffer::Peek()
{
	return m_ptr + m_start;
}

void CBuffer::Expand(int sz)
{
	char *ptr = new char[sz];
	memcpy(ptr, m_ptr + m_start, m_end - m_start);
	m_end -= m_start;
	m_start = 0;
	m_capacity = sz;
	delete[] m_ptr;
	m_ptr = ptr;
}

void CBuffer::Collect()
{
	if(m_start == 0)
	{
		return ;
	}
	memmove(m_ptr + m_start, m_ptr, m_end - m_start);
	m_end -= m_start;
	m_start = 0;
}

int CBuffer::Capacity()
{
	return m_capacity;
}

int CBuffer::Size()
{
	return m_end - m_start;
}

bool CBuffer::Empty()
{
	return m_start == m_end;
}
