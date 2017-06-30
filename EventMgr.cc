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

int CEventMgr::Run()
{
	while(1)
	{
		if(m_status == STATUS_STOP)
		{
			break;
		}
		std::map<int, int> events;
		if(-1 == m_event->LoopEvent(-1, events))
		{
			break;
		}
		for(std::map<int, int>::const_iterator i = events.begin(); i != events.end(); ++i)
		{
			std::map<int, CBaseSocket *>::iterator j = m_sockets.find(i->first);
			if(j == m_sockets.end())
			{
				continue;
			}
			if(i->second & EV_READ)
			{
				j->second->Read(this);
			}
			if(i->second & EV_WRITE)
			{
				j->second->Send(this);
			}
		}
	}
	return 0;
}

CEventMgr::~CEventMgr()
{
	for(std::map<int, CBaseSocket *>::const_iterator itr = m_sockets.begin(); itr != m_sockets.end(); ++itr)
	{
		delete itr->second;
	}
	m_sockets.clear();
	delete m_event;
}

int CEventMgr::AddEvent(int fd, int events)
{
	m_event->AddEvent(fd, events);
	return 0;
}

int CEventMgr::AddEvent(int fd, CBaseSocket *s, int events)
{
	if(0 != AddEvent(fd, events))
	{
		return -1;
	}
	m_sockets[fd] = s;
	return 0;
}

int CEventMgr::DelEvent(int fd)
{
	std::map<int, CBaseSocket *>::iterator itr = m_sockets.find(fd);
	if(itr == m_sockets.end())
	{
		return 0;
	}
	m_event->DelEvent(fd);
	delete itr->second;
	m_sockets.erase(itr);
	return 0;
}

int CEventMgr::InitServer(const char *host, int port)
{
	if(Init() != 0)
	{
		return -1;
	}
	CServerSocket *s = new CServerSocket();
	if(s->Init(host, port) != 0)
	{
		delete s;
		return -1;
	}
	int fd = s->GetFd();
	if(0 != AddEvent(fd, EV_READ))
	{
		delete s;
		return -1;
	}
	m_sockets.insert(std::make_pair(fd, s));
	return 0;
}
