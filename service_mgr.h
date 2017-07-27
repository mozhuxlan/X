#ifndef __SERVICE_MGR_H__
#define __SERVICE_MGR_H__

#include "service.h"
#include <map>

class CServiceMgr
{
public:
	CServiceMgr() = default;
	~CServiceMgr();
	CServiceMgr(const CServiceMgr &rhs) = delete;
	CServiceMgr& operator=(CServiceMgr &rhs) = delete;

public:
	CService *CreateService(E_SERVICE_TYPE type, const char *param);
	CService *GetService(int serviceId);
	void DelService(int serviceId);

private:
	int AllocServiceId();

private:
	std::map<int, CService *> m_services;
};

#endif
