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

void CBuffer::Expand(size_t n)
{
	char *ptr = (char *)malloc(n);
	memcpy(ptr, m_data + m_begin, m_end - m_begin);
	m_end -= m_begin;
	m_begin = 0;
	m_capacity = n;
	free(m_data);
	m_data = ptr;
}

void CBuffer::Push(const char *str, size_t n)
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
	}
	else
	{
		Expand(m_capacity * 2 + n);
		memcpy(m_data + m_end, str, n);
	}

}

void CBuffer::Remove(size_t n)
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

size_t CBuffer::Size()
{
	return m_end - m_begin;
}

const char *CBuffer::Peek()
{
	return m_data + m_begin;
}
