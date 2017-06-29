#ifndef __EVENT_H__
#define __EVENT_H__

#include <sys/select.h>

class CBaseEvent
{
public:
	CBaseEvent() {}
	virtual ~CBaseEvent() {}

public:
	virtual int InitEvent() = 0;
	virtual int AddEvent() = 0;
	virtual int ModEvent() = 0;
	virtual int DelEvent() = 0;
	virtual int LoopEvent(int timeout) = 0;


};

#ifdef __linux__
class CEpollEvent : public CBaseEvent
{
public:
	CEpollEvent(); 

	~CEpollEvent();

public:
	virtual int InitEvent();
	virtual int AddEvent();
	virtual int ModEvent();
	virtual int DelEvent();
	virtual int LoopEvent(int timeout);

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
	virtual int AddEvent();
	virtual int ModEvent();
	virtual int DelEvent();
	virtual int LoopEvent(int timeout);

private:
	fd_set m_rfd;
	fd_set m_wfd;
	int m_maxfd;
};

#endif
