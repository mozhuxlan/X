#include <unistd.h>
#include <sys/epoll.h>
#include "socket.h"
#include "event.h"

CEventMgr::~CEventMgr()
{
	for(std::map<int, CSocket *>::iterator itr = m_events.begin(); itr != m_events.end(); ++itr)
	{
		DelEvent(itr->first);
		delete itr->second;
	}
	m_events.clear();
	close(m_fd);
}

int CEventMgr::Init()
{
	int efd = epoll_create(1024);
	if(-1 == efd)
	{
		return -1;
	}
	m_fd = efd;
	return 0;
}

int CEventMgr::Start()
{
	while(1)
	{
		struct epoll_event evs[1024];
		int ret = epoll_wait(m_fd, evs, 1024, -1);
		if(-1 == ret)
		{
			break;
		}
		int i;
		for(i = 0; i < ret; ++i)
		{
			if(evs[i].events & EPOLLIN)
			{
				ReadEvent(evs[i].data.fd);
			}
			if(evs[i].events & EPOLLOUT)
			{
				WriteEvent(evs[i].data.fd);
			}
		}
	}
	return 0;
}

int CEventMgr::CreateSocket(E_SOCKET_TYPE type, const char *host, int port)
{
	CSocket *s = nullptr;
	switch(type)
	{
		case E_SOCKET_TYPE::SERVER:
			s = new CServerSocket();
			break;
		case E_SOCKET_TYPE::CLIENT:
			s = new CClientSocket();
			break;
		default:
			return -1;
	}
	if(s->Init(host, port) != 0)
	{
		delete s;
		return -1;
	}
	m_events.insert(std::make_pair(s->GetFd(), s));
	return AddEvent(s->GetFd());
}

int CEventMgr::AddEvent(int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	return epoll_ctl(m_fd, EPOLL_CTL_ADD, fd, &ev);
}

int CEventMgr::DelEvent(int fd)
{
	return epoll_ctl(m_fd, EPOLL_CTL_DEL, fd, NULL);
}

int CEventMgr::ReadEvent(int fd)
{
	std::map<int, CSocket *>::iterator itr = m_events.find(fd);
	if(itr == m_events.end())
	{
		DelEvent(fd);
		return 0;
	}
	int ret = itr->second->Read();
	if(-1 == ret)
	{
		DelEvent(fd);
		delete itr->second;
		m_events.erase(fd);
		return 0;
	}
	if(ret > 0)
	{
		CSocket *s = new CClientSocket(ret);
		m_events.insert(std::make_pair(ret, s));
		return AddEvent(ret);
	}
	return 0;
}

int CEventMgr::WriteEvent(int fd)
{
	std::map<int, CSocket *>::iterator itr = m_events.find(fd);
	if(itr == m_events.end())
	{
		DelEvent(fd);
		return 0;
	}
	int ret = itr->second->Write();
	if(-1 == ret)
	{
		DelEvent(fd);
		delete itr->second;
		m_events.erase(fd);
		return 0;
	}
	return 0;
}
