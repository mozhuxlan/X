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

int CEpollEvent::InitEvent()
{
	m_efd = epoll_create(10);
	if(-1 == m_efd)
	{
		return -1;
	}
	return 0;
}

int CEpollEvent::AddEvent(int fd, int events)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	if(events & EV_READ)
	{
		ev.events |= EPOLLIN;
	}
	if(events & EV_WRITE)
	{
		ev.events |= EPOLLOUT;
	}
	return epoll_ctl(m_efd, EPOLL_CTL_ADD, fd, &ev);
}

int CEpollEvent::ModEvent(int fd, int events)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	if(events & EV_READ)
	{
		ev.events |= EPOLLIN;
	}
	if(events & EV_WRITE)
	{
		ev.events |= EPOLLOUT;
	}
	return epoll_ctl(m_efd, EPOLL_CTL_MOD, fd, &ev);
}

int CEpollEvent::DelEvent(int fd)
{
	return epoll_ctl(m_efd, EPOLL_CTL_DEL, fd, NULL);
}

int CEpollEvent::LoopEvent(int timeout, std::map<int, int> &events)
{
	struct epoll_event evs[1024];
	int n = epoll_wait(m_efd, evs, 1024, timeout);
	if(-1 == n)
	{
		return -1;
	}
	if(0 == n)
	{
		// timeout event
		return 0;
	}
	for(int i = 0; i < n; ++i)
	{
		if(evs[i].events & EPOLLIN)
		{
			events[i] |= EV_READ;
		}
		if(evs[i].events & EPOLLOUT)
		{
			events[i] |= EV_WRITE;
		}
	}
	return 0;
}
#endif

CSelectEvent::CSelectEvent() : CBaseEvent()
{
}

CSelectEvent::~CSelectEvent()
{
}

int CSelectEvent::InitEvent()
{
	FD_ZERO(&m_rfd);
	FD_ZERO(&m_wfd);
	return 0;
}

int CSelectEvent::AddEvent(int fd, int events)
{
	if(events & EV_READ)
	{
		FD_SET(fd, &m_rfd);
	}
	if(events & EV_WRITE)
	{
		FD_SET(fd, &m_wfd);
	}
	if(m_maxfd < fd)
	{
		m_maxfd = fd;
	}
	return 0;
}

int CSelectEvent::ModEvent(int fd, int events)
{
	FD_CLR(fd, &m_rfd);
	FD_CLR(fd, &m_wfd);
	if(events & EV_READ)
	{
		FD_SET(fd, &m_rfd);
	}
	if(events & EV_WRITE)
	{
		FD_SET(fd, &m_wfd);
	}
	return 0;
}

int CSelectEvent::DelEvent(int fd)
{
	FD_CLR(fd, &m_rfd);
	FD_CLR(fd, &m_wfd);
	return 0;
}

int CSelectEvent::LoopEvent(int timeout, std::map<int, int> &events)
{
	//struct timeval tv;
	//tv.tv_sec = timeout;
	//tv.tv_usec = 0;
	fd_set rfd, wfd;
	rfd = m_rfd;
	wfd = m_wfd;
	int n = select(m_maxfd + 1, &rfd, &wfd, NULL, NULL);
	if(-1 == n)
	{
		return -1;
	}
	for(int i = 0;i < m_maxfd + 1; ++i)
	{
		if(FD_ISSET(i, &rfd))
		{
			events[i] |= EV_READ;
		}
		if(FD_ISSET(i, &wfd))
		{
			events[i] |= EV_WRITE;
		}
	}
	return 0;
}
