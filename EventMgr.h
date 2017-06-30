#ifndef __EVENT_MGR_H__
#define __EVENT_MGR_H__


#include "Event.h"
#include <map>
#include "Socket.h"

#define STATUS_RUNNING	0x01
#define STATUS_STOP		0x02

class CEventMgr
{
public:
	CEventMgr();
	~CEventMgr();

public:
	CEventMgr(const CEventMgr &rhs) = delete;
	CEventMgr &operator=(const CEventMgr &rhs) = delete;

private:
	int Init();

public:
	int Run();
	int InitServer(const char *host, int port);
	int AddEvent(int fd, int events);
	int AddEvent(int fd, CBaseSocket *s, int events);
	int DelEvent(int fd);

private:
	CBaseEvent *m_event;
	int m_status;
	std::map<int, CBaseSocket *> m_sockets;
};

#endif
