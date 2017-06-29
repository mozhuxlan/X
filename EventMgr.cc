#include "EventMgr.h"
#include <stdio.h>

CEventMgr::CEventMgr() : m_event(NULL), m_status(STATUS_STOP)
{}

int CEventMgr::Init()
{
#ifdef __linux__
	m_event = new CEpollEvent;
#else
	m_event = new CSelectEvent;
#endif
	if(0 != m_event->InitEvent())
	{
		return -1;
	}
	m_status = STATUS_RUNNING;
	return 0;
}

void CEventMgr::Run()
{
	while(1)
	{
		if(m_status == STATUS_STOP)
		{
			break;
		}
		if(-1 == m_event->LoopEvent(1))
		{
			break;
		}
	}
}

CEventMgr::~CEventMgr()
{
	delete m_event;
}
