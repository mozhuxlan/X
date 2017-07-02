#ifndef __BUFFER_H__
#define __BUFFER_H__

class CBuffer
{
public:
	CBuffer();
	~CBuffer();
	CBuffer(const CBuffer &rhs);
	CBuffer &operator=(const CBuffer &rhs);
#if __cplusplus >= 201103L
	CBuffer(CBuffer &&rhs);
	CBuffer &operator=(CBuffer &&rhs);
#endif

private:
	void Expand(int n);

public:
	int Size() const;
	void Push(const char *str, int n);
	void Remove(int n);
	void Clear();
	bool Empty();
	const char *Peek() const;

private:
	char *m_data;
	int m_begin;
	int m_end;
	int m_capacity;
};

#endif
