#ifndef __EVENT_MGR_H__
#define __EVENT_MGR_H__


#include "Event.h"

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

public:
	int Init();
	void Run();

private:
	CBaseEvent *m_event;
	int m_status;
};

#endif
