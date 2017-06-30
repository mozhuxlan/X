#ifndef __SOCKET_H__
#define __SOCKET_H__

class CEventMgr;

class CBaseSocket
{
public:
	CBaseSocket();
	CBaseSocket(int fd) : m_fd(fd) {}
	virtual ~CBaseSocket();

public:
	virtual int Init(const char *host, int port) = 0;
	virtual int Send(CEventMgr *em) = 0;
	virtual int Read(CEventMgr *em) = 0;

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
	int Send(CEventMgr *em) override;
	int Read(CEventMgr *em) override;
};

class CClientSocket : public CBaseSocket
{
public:
	CClientSocket() : CBaseSocket() {}
	CClientSocket(int fd) : CBaseSocket(fd) {}
	~CClientSocket() {}

public:
	int Init(const char *host, int port) override;
	int Send(CEventMgr *em) override;
	int Read(CEventMgr *em) override;
};


#endif
