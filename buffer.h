#ifndef __BUFFER_H__
#define __BUFFER_H__

class CBuffer
{
public:
	CBuffer();
	~CBuffer();
	CBuffer(const CBuffer &rhs);
	CBuffer &operator= (const CBuffer &rhs);
	CBuffer(CBuffer &&rhs);
	CBuffer &operator= (CBuffer &&rhs);


public:
	void Add(const char *str, int len);
	void Del(int len);
	void Clear();
	const char* Peek();
	bool Empty();
	int Capacity();
	int Size();

private:
	void Expand(int sz);
	void Collect();

private:
	int m_start;
	int m_end;
	int m_capacity;
	char *m_ptr;
};

#endif
