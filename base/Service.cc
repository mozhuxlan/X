#include "Service.h"
#include <mysql.h>


CService::CService(int serviceId) : m_nServiceId(serviceId)
{
}

CService::~CService()
{
}

CDBService::CDBService(int serviceId) : CService(serviceId)/*, m_handler(NULL)*/
{}

CDBService::~CDBService()
{
	if(m_handler)
	{
		// mysql_close(m_handler);
	}
}

int CDBService::Init(const char *cmd)
{
	return 0;
}

int CDBService::Callback(int sessId, void *msg)
{
	return 0;
}

int CDBService::Destroy()
{
	return 0;
}
