#include "Event.h"
#ifdef __linux__
#include <sys/epoll.h>
#else
#endif
#include <unistd.h>
#include <sys/time.h>


#ifdef __linux__
CEpollEvent::CEpollEvent() : CBaseEvent(), m_efd(-1)
{
}

CEpollEvent::~CEpollEvent()
{
	if(-1 == m_efd)
	{
		return;
	}
	close(m_efd);
}

int CEpollEvent::Init()
{
	m_efd = epoll_create(10);
	if(-1 == m_efd)
	{
		return -1;
	}
	return 0;
}

int CEpollEvent::AddEvent()
{
	return 0;
}

int CEpollEvent::ModEvent()
{
	return 0;
}

int CEpollEvent::DelEvent()
{
	return 0;
}

int CEpollEvent::LoopEvent(int timeout)
{
	struct epoll_event evs[1024];
	int n = epoll_wait(m_efd, evs, 1024, timeout);
	if(-1 == n)
	{
		return -1;
	}
	if(0 == n)
	{
		//timeout
		return 0;
	}
	for(int i = 0; i < n; ++i)
	{
		if(evs[i].events & EPOLLIN)
		{
			// read;
		}
		if(evs[i].events & EPOLLOUT)
		{
			// write;
		}
	}
	return 0;
}
#endif

CSelectEvent::CSelectEvent() : CBaseEvent()
{
	FD_ZERO(&m_rfd);
	FD_ZERO(&m_wfd);
}

CSelectEvent::~CSelectEvent()
{
}

int CSelectEvent::InitEvent()
{
	return 0;
}

int CSelectEvent::AddEvent()
{
	return 0;
}

int CSelectEvent::ModEvent()
{
	return 0;
}

int CSelectEvent::DelEvent()
{
	return 0;
}

int CSelectEvent::LoopEvent(int timeout)
{
	struct timeval tv;
	tv.tv_sec = timeout;
	tv.tv_usec = 0;
	fd_set rfd, wfd;
	rfd = m_rfd;
	wfd = m_wfd;
	int n = select(m_maxfd, &rfd, &wfd, NULL, &tv);
	if(n == 0)
	{
		// timeout
	}
	for(int i = 0; i < m_maxfd; ++i)
	{
		// something happen
	}
	return 0;
}
