#include "agent_service.h"

CAgentService::CAgentService(int serviceId) : CService(serviceId, E_SERVICE_TYPE::AGENT)
{
}

CAgentService::~CAgentService()
{
}

int CAgentService::Init(const char *param)
{
	return 0;
}

int CAgentService::Callback()
{
	return 0;
}
