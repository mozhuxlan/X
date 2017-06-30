#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdio.h>

class CBuffer
{
public:
	CBuffer();
	~CBuffer();
	CBuffer(const CBuffer &rhs);
	CBuffer &operator=(const CBuffer &rhs);

private:
	void Expand(size_t n);

public:
	void Push(const char *str, size_t n);
	void Remove(size_t n);
	void Clear();
	size_t Size();
	bool Empty();
	const char *Peek();

private:
	char *m_data;
	size_t m_begin;
	size_t m_end;
	size_t m_capacity;
};

#endif
