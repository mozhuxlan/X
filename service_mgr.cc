#include "service_mgr.h"
#include "agent_service.h"
#include "db_service.h"
#include <limits.h>

CServiceMgr::~CServiceMgr()
{
	for(std::map<int, CService *>::iterator itr = m_services.begin(); itr != m_services.end(); ++itr)
	{
		delete itr->second;
	}
	m_services.clear();
}

int CServiceMgr::AllocServiceId()
{
	int i;
	for(i = 0; i < INT_MAX; ++i)
	{
		if(m_services.find(i) == m_services.end())
		{
			return i;
		}
	}
	return -1;
}

CService *CServiceMgr::CreateService(E_SERVICE_TYPE type, const char *param)
{
	CService *s = nullptr;
	int serviceId = AllocServiceId();
	if(-1 == serviceId)
	{
		return s;
	}
	switch(type)
	{
		case E_SERVICE_TYPE::AGENT:
			s = new CAgentService(serviceId);
			break;
		case E_SERVICE_TYPE::DB:
			s = new CDBService(serviceId);
		default:
			return nullptr;
	}
	s->Init(param);
	return s;
}

CService *CServiceMgr::GetService(int serviceId)
{
	std::map<int, CService *>::iterator itr = m_services.find(serviceId);
	if(itr == m_services.end())
	{
		return nullptr;
	}
	return itr->second;
}

void CServiceMgr::DelService(int serviceId)
{
	std::map<int, CService *>::iterator itr = m_services.find(serviceId);
	if(itr == m_services.end())
	{
		return ;
	}
	delete itr->second;
	m_services.erase(itr);
}
