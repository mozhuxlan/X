#include "Buffer.h"
#include <string.h>
#include <stdlib.h>

CBuffer::CBuffer() : m_data(nullptr), m_begin(0), m_end(0), m_capacity(0)
{}

CBuffer::~CBuffer()
{
	if(m_data != nullptr)
	{
		return;
	}
	free(m_data);
	m_data = NULL;
}

CBuffer::CBuffer(const CBuffer &rhs)
{
	m_data = (char *)malloc(rhs.m_capacity);
	memcpy(m_data, rhs.m_data, rhs.m_capacity);
	m_begin = rhs.m_begin;
	m_end = rhs.m_end;
	m_capacity = rhs.m_capacity;
}

CBuffer &CBuffer::operator=(const CBuffer &rhs)
{
	if(&rhs == this)
	{
		return *this;
	}
	if(m_data != nullptr)
	{
		free(m_data);
	}
	m_data = (char *)malloc(rhs.m_capacity);
	memcpy(m_data, rhs.m_data, rhs.m_capacity);
	m_begin = rhs.m_begin;
	m_end = rhs.m_end;
	m_capacity = rhs.m_capacity;
	return *this;
}

void CBuffer::Expand(int n)
{
	char *ptr = (char *)malloc(n);
	memcpy(ptr, m_data + m_begin, m_end - m_begin);
	m_end -= m_begin;
	m_begin = 0;
	m_capacity = n;
	if(m_data != nullptr)
	{
		free(m_data);
	}
	m_data = ptr;
}

void CBuffer::Push(const char *str, int n)
{
	if(m_capacity - m_end > n)
	{
		memcpy(m_data + m_end, str, n);
		return;
	}
	else if(m_capacity + m_begin - m_end > n)
	{
		memmove(m_data, m_data + m_begin, m_end - m_begin);
		m_end -= m_begin;
		m_begin = 0;
		memcpy(m_data + m_end, str, n);
		m_end += n;
	}
	else
	{
		Expand(m_capacity * 2 + n);
		memcpy(m_data + m_end, str, n);
		m_end += n;
	}

}

void CBuffer::Remove(int n)
{
	m_begin += n;
	if(m_begin > m_end)
	{
		m_begin = m_end = 0;
	}
}

bool CBuffer::Empty()
{
	return m_begin == m_end;
}

void CBuffer::Clear()
{
	m_begin = m_end = 0;
}

int CBuffer::Size() const
{
	return m_end - m_begin;
}

const char *CBuffer::Peek() const
{
	return m_data + m_begin;
}

#if __cplusplus >= 201103L
CBuffer::CBuffer(CBuffer &&rhs)
{
	m_capacity = rhs.m_capacity;
	m_begin = rhs.m_begin;
	m_end = rhs.m_end;
	m_data = rhs.m_data;
	rhs.m_data = NULL;
	rhs.m_capacity = 0;
	rhs.m_begin = 0;
	rhs.m_end = 0;
}

CBuffer &CBuffer::operator=(CBuffer &&rhs)
{
	if(&rhs == this)
	{
		return *this;
	}
	m_capacity = rhs.m_capacity;
	m_begin = rhs.m_begin;
	m_end = rhs.m_end;
	m_data = rhs.m_data;
	rhs.m_data = NULL;
	rhs.m_capacity = 0;
	rhs.m_begin = 0;
	rhs.m_end = 0;
	return *this;
}
#endif
