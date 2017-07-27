#include "server.h"
#include <pthread.h>
#include <functional>

CServer::CServer()
{}

CServer::~CServer()
{}


int CServer::Init(const CConfig &cfg)
{
	if(m_event.Init() != 0)
	{
		return -1;
	}

	if(m_event.CreateSocket(E_SOCKET_TYPE::SERVER, "0.0.0.0", 9057) != 0)
	{
		return -1;
	}

	m_state = E_SERVER_STATE::RUN;
	return 0;
}

void *CServer::StartSocket(void *arg)
{
	CServer *self = static_cast<CServer *>(arg);
	while(1)
	{
		if(self->m_state == E_SERVER_STATE::STOP)
		{
			break;
		}
		int ret = self->m_event.Loop(-1);
		if(-1 == ret)
		{
			break;
		}
		if(0 == ret)
		{
			// TODO timeout
		}
	}
	return NULL;
}

void *CServer::StartLoop(void *arg)
{
	CServer *self = static_cast<CServer *>(arg);
	while(1)
	{
		if(self->m_state == E_SERVER_STATE::STOP)
		{
			break;
		}

	}
	return NULL;
}

int CServer::Start()
{
	if(m_state != E_SERVER_STATE::RUN)
	{
		return -1;
	}
	pthread_create(&m_threads[0], NULL, CServer::StartSocket, this);
	int i = 1;
	for(i = 1; i < 20; ++i)
	{
		pthread_create(&m_threads[i], NULL, CServer::StartLoop, this);
	}
	for(i = 0; i < 20; ++i)
	{
		pthread_join(m_threads[i], NULL);
	}
	return 0;
}

void CServer::Stop()
{
	m_state = E_SERVER_STATE::STOP;
}

void CServer::Destroy()
{
}
