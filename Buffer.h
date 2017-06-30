#ifndef __BUFFER_H__
#define __BUFFER_H__

class CBuffer
{
public:
	CBuffer();
	~CBuffer();
	CBuffer(const CBuffer &rhs);
	CBuffer &operator=(const CBuffer &rhs);

private:
	void Expand(int n);

public:
	void Push(const char *str, int n);
	void Remove(int n);
	void Clear();
	int Size();
	bool Empty();
	const char *Peek();

private:
	char *m_data;
	int m_begin;
	int m_end;
	int m_capacity;
};

#endif
