#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "Socket.h"
#include "EventMgr.h"


CBaseSocket::CBaseSocket() : m_fd(-1)
{}

CBaseSocket::~CBaseSocket() 
{
	if(-1 == m_fd)
	{
		return;
	}
	close(m_fd);
}

int CBaseSocket::GetFd()
{
	return m_fd;
}


int CServerSocket::Init(const char *host, int port)
{
	m_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == m_fd)
	{
		return -1;
	}

	int flag = fcntl(m_fd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(m_fd, F_SETFL, flag);

	int optval = 1;
	size_t optlen = sizeof(optval);
	setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &optval, optlen);
	setsockopt(m_fd, SOL_SOCKET, SO_REUSEPORT, &optval, optlen);

	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.s_addr = inet_addr(host);
	if(-1 == bind(m_fd, (struct sockaddr *)&si, sizeof(struct sockaddr)))
	{
		return -1;
	}
	if(-1 == listen(m_fd, 128))
	{
		return -1;
	}
	return 0;
}

int CServerSocket::Send(CEventMgr *em)
{
	return -1;
}

int CServerSocket::Read(CEventMgr *em)
{
	while(1)
	{
		struct sockaddr_in si;
		socklen_t socklen = sizeof(struct sockaddr);
		int cfd = accept(m_fd, (struct sockaddr *)&si, &socklen);
		if(-1 == cfd)
		{
			if(EAGAIN == errno || EINTR == errno)
			{
				break;
			}
			return -1;
		}
		CClientSocket *s = new CClientSocket(cfd);
		if(0 != em->AddEvent(cfd, s, EV_READ | EV_WRITE))
		{
			delete s;
			return -1;
		}
	}
	return 0;
}

int CClientSocket::Init(const char *host, int port)
{
	m_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == m_fd)
	{
		return -1;
	}
	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.s_addr = inet_addr(host);

	if(-1 == connect(m_fd, (struct sockaddr *)&si, sizeof(struct sockaddr)))
	{
		return -1;
	}

	int flag = fcntl(m_fd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(m_fd, F_SETFL, flag);

	return 0;
}

int CClientSocket::Read(CEventMgr *em)
{
	char buf[1024] = {0};
	int n = recv(m_fd, buf, 1024, 0);
	if(n <= 0)
	{
		if(EAGAIN == errno || EINTR == errno)
		{
			return 0;
		}
		em->DelEvent(m_fd);
		return -1;
	}
	printf("[%d] say : %s\n", m_fd, buf);
	return 0;
}

int CClientSocket::Send(CEventMgr *em)
{
	return 0;
}
