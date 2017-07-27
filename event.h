#ifndef __EVENT_H__
#define __EVENT_H__

#include <map>

class CSocket;


enum class E_SOCKET_TYPE
{
	SERVER = 1,
	CLIENT = 2
};

class CEventMgr
{
public:
	CEventMgr() = default;
	~CEventMgr();

public:
	int CreateSocket(E_SOCKET_TYPE type, const char *host, int port);

private:
	int AddEvent(int fd);
	int DelEvent(int fd);

private:
	int ReadEvent(int fd);
	int WriteEvent(int fd);

public:
	int Init();
	int Loop(int timeout);

private:
	int m_fd;
	std::map<int, CSocket *> m_events;
};

#endif
