#include "server.h"
#include <pthread.h>

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

int CServer::Start()
{
	m_event.Start();
	return 0;
}

void CServer::Stop()
{
	m_state = E_SERVER_STATE::STOP;
}

void CServer::Destroy()
{
}
