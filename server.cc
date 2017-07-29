#include "server.h"
#include <pthread.h>
#include <functional>
#include <unistd.h>

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
	int i;
	// Test 
	const char *ptr = "host username passwd db";
	for(i = 0; i < 10; ++i)
	{
		m_service.CreateService(E_SERVICE_TYPE::DB, ptr);
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
		sleep(1);
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
