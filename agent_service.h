#ifndef __AGENT_SERVICE_H__
#define __AGENT_SERVICE_H__

#include "service.h"

class CAgentService : public CService 
{
public:
	CAgentService(int serviceId);
	~CAgentService();

public:
	virtual int Init(const char *param) override;
	virtual int Callback() override;
};

#endif
