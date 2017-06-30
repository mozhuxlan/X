#ifndef __EVENT_H__
#define __EVENT_H__

#ifndef __linux__
#include <sys/select.h>
#endif

#include <map>

#define EV_READ				0x01
#define EV_WRITE			0x02


class CBaseEvent
{
public:
	CBaseEvent() {}
	virtual ~CBaseEvent() {}

public:
	virtual int InitEvent() = 0;
	virtual int AddEvent(int fd, int events) = 0;
	virtual int ModEvent(int fd, int events) = 0;
	virtual int DelEvent(int fd) = 0;
	virtual int LoopEvent(int timeout, std::map<int, int> &events) = 0;


};

#ifdef __linux__
class CEpollEvent : public CBaseEvent
{
public:
	CEpollEvent(); 

	~CEpollEvent();

public:
	virtual int InitEvent();
	virtual int AddEvent(int fd, int events);
	virtual int ModEvent(int fd, int events);
	virtual int DelEvent(int fd);
	virtual int LoopEvent(int timeout, std::map<int, int> &events);

private:
	int m_efd;
};
#endif

class CSelectEvent : public CBaseEvent
{
public:
	CSelectEvent();
	~CSelectEvent();

public:
	virtual int InitEvent();
	virtual int AddEvent(int fd, int events);
	virtual int ModEvent(int fd, int events);
	virtual int DelEvent(int fd);
	virtual int LoopEvent(int timeout, std::map<int, int> &events);

private:
	fd_set m_rfd;
	fd_set m_wfd;
	int m_maxfd;
};

#endif
