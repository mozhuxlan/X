#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "Buffer.h"

class CBaseSocket
{
public:
	CBaseSocket();
	CBaseSocket(int fd) : m_fd(fd) {}
	virtual ~CBaseSocket();

public:
	virtual int Init(const char *host, int port) = 0;
	virtual int Send() = 0;
	virtual int Send(const char *str, int n) = 0;
	virtual int Read() = 0;

public:
	int GetFd();

protected:
	int m_fd;
};


class CServerSocket : public CBaseSocket
{
public:
	CServerSocket() : CBaseSocket() {}
	~CServerSocket(){}

public:
	int Init(const char *host, int port) override;
	int Send() override;
	int Send(const char *str, int n) override;
	int Read() override;
};

class CClientSocket : public CBaseSocket
{
public:
	CClientSocket() : CBaseSocket() {}
	CClientSocket(int fd) : CBaseSocket(fd) {}
	~CClientSocket() {}

public:
	int Init(const char *host, int port) override;
	int Send() override;
	int Send(const char *str, int n) override;
	int Read() override;

private:
	CBuffer m_rb;
	CBuffer m_sb;
};


#endif
