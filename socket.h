#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "buffer.h"

class CSocket
{
public:
	CSocket(int fd = -1);
	virtual ~CSocket();

public:
	virtual int Init(const char *host, int port) = 0;
	virtual int Read() = 0;
	virtual int Write() = 0;

public:
	int GetFd() { return m_fd; }

protected:
	int m_fd;
};

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	~CServerSocket();

public:
	virtual int Init(const char *host, int port) override;
	virtual int Read() override;
	virtual int Write() override;
};

class CClientSocket : public CSocket
{ 
public:
	CClientSocket();
	CClientSocket(int fd);
	~CClientSocket();

public:
	virtual int Init(const char *host, int port) override;
	virtual int Read() override;
	virtual int Write() override;

private:
	CBuffer m_rb;
	CBuffer m_sb;
};

#endif
