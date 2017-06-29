#ifndef __SOCKET_H__
#define __SOCKET_H__

class CBaseSocket
{
public:
	CBaseSocket();
	virtual ~CBaseSocket();

public:
	virtual int Init(const char *host, int port) = 0;
	virtual int Send() = 0;
	virtual int Read() = 0;

protected:
	int m_fd;
};


class CServerSocket : public CBaseSocket
{
public:
	CServerSocket() : CBaseSocket() {}
	~CServerSocket(){}

public:
	int Init(const char *host, int port);
	int Send();
	int Read();
};

class CClientSocket : public CBaseSocket
{
public:
	CClientSocket() : CBaseSocket() {}
	~CClientSocket() {}

public:
	int Init(const char *host, int port);
	int Send();
	int Read();
};


#endif
