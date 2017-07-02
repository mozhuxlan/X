#ifndef __SOCKET_MGR_H__
#define __SOCKET_MGR_H__

#include <map>
#include "Event.h"
#include "Socket.h"

#define STATUS_RUNNING	0x01
#define STATUS_STOP		0x02

class CSocketMgr
{
public:
	CSocketMgr();
	~CSocketMgr();

public:
	CSocketMgr(const CSocketMgr &rhs) = delete;
	CSocketMgr &operator=(const CSocketMgr &rhs) = delete;

private:
	int Init();

public:
	int Run();
	int Stop();
	int InitServer(const char *host, int port);
	int AddSocket(CBaseSocket *s, int events);
	int DelSocket(CBaseSocket *s);

private:
	int m_status;
	CBaseEvent *m_event;
	std::map<int, CBaseSocket *> m_sockets;
};

#endif
