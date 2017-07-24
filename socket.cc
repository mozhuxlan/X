#include "socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

CSocket::CSocket(int fd) : m_fd(fd)
{}

CSocket::~CSocket()
{
	close(m_fd);
}


CServerSocket::CServerSocket() : CSocket()
{}

CServerSocket::~CServerSocket()
{}

int CServerSocket::Init(const char *host, int port)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == fd)
	{
		printf("[%s:%d] [ERROR] %s\n", __FILE__, __LINE__, strerror(errno));
		return -1;
	}

	int optval = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	int flag = fcntl(fd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flag);

	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.s_addr = inet_addr(host);

	if(-1 == bind(fd, (struct sockaddr *)&si, sizeof(si)))
	{
		printf("[%s:%d] [ERROR] %s\n", __FILE__, __LINE__, strerror(errno));
		return -1;
	}

	if(-1 == listen(fd, 128))
	{
		printf("[%s:%d] [ERROR] %s\n", __FILE__, __LINE__, strerror(errno));
		return -1;
	}

	m_fd = fd;
	return 0;
}

int CServerSocket::Read()
{
	struct sockaddr_in si;
	socklen_t len;
	int fd = accept(m_fd, (struct sockaddr *)&si, &len);
	if(-1 == fd)
	{
		if(errno != EINTR && errno != EAGAIN)
		{
			return -1;
		}
		return 0;
	}
	return fd;
}

int CServerSocket::Write()
{
	return 0;
}


CClientSocket::CClientSocket() : CSocket()
{}

CClientSocket::CClientSocket(int fd) : CSocket(fd)
{
	int flag = fcntl(fd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flag);
}

CClientSocket::~CClientSocket()
{}


int CClientSocket::Init(const char *host, int port)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == fd)
	{
		printf("[%s:%d] [ERROR] %s\n", __FILE__, __LINE__, strerror(errno));
		return -1;
	}

	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.s_addr = inet_addr(host);

	if(-1 == connect(fd, (struct sockaddr *)&si, sizeof(si)))
	{
		printf("[%s:%d] [ERROR] %s\n", __FILE__, __LINE__, strerror(errno));
		return -1;
	}

	int flag = fcntl(fd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flag);

	m_fd = fd;
	return 0;
}

int CClientSocket::Read()
{
	char buf[1024] = {0};
	int n = recv(m_fd, buf, 1024, 0);
	if(n <= 0)
	{
		if(errno != EINTR && errno != EAGAIN)
		{
			return -1;
		}
		return 0;
	}
	m_rb.Add(buf, n);
	/*
	if(m_rb.Size() < (int)sizeof(int))
	{
		return 0;
	}
	const char *ptr = m_rb.Peek();
	int sz = ptr[3] << 24 | ptr[2] << 16 | ptr[1] << 8 | ptr[0];
	if(sz > m_rb.Size())
	{
		return 0;
	}
	printf("fd[%d] recv data = %s\n", m_fd, ptr + 4);
	m_rb.Del(sz + 4);
	*/
	return 0;
}

int CClientSocket::Write()
{
	if(m_sb.Empty())
	{
		return 0;
	}
	int sz = m_sb.Size();
	const char *str = m_rb.Peek();
	char buf[4] = {0};
	buf[3] = sz >> 24;
	buf[2] = sz >> 16;
	buf[1] = sz >> 8;
	buf[0] = sz;
	if(-1 == send(m_fd, buf, 4, 0))
	{
		return -1;
	}
	int pos = 0;
	while(1)
	{
		int ret = send(m_fd, str + pos, sz - pos, 0);
		if(-1 == ret)
		{
			return -1;
		}
		if(pos + ret == sz)
		{
			break;
		}
		pos += ret;
	}
	return 0;
}
