#include "db_service.h"
#include <string.h>

CDBService::CDBService(int serviceId) : CService(serviceId, E_SERVICE_TYPE::DB), m_handler(NULL)
{
}

CDBService::~CDBService()
{
	if(m_handler != NULL)
	{
		mysql_close(m_handler);
	}
}

int CDBService::ParseParam(const char *param)
{
	char *ptr0 = strchr((char *)param, ' ');
	m_host.assign(param, ptr0 - param);

	char *ptr1 = strchr(ptr0 + 1, ' ');
	m_username.assign(ptr0 + 1, ptr1);

	char *ptr2 = strchr(ptr1 + 1, ' ');
	m_passwd.assign(ptr1 + 1, ptr2);

	char *ptr3 = strchr(ptr2 + 1, ' ');
	m_db.assign(ptr2 + 1, ptr3);
	return 0;
}

int CDBService::Init(const char *param)
{
	if(0 != ParseParam(param))
	{
		return -1;
	}
	m_handler = mysql_init(NULL);
	if(!mysql_real_connect(m_handler, m_host.c_str(), m_username.c_str(), m_passwd.c_str(), m_db.c_str(), 0, NULL, 0))
	{
		printf("[%s:%d] %s\n", __FILE__, __LINE__, mysql_error(m_handler));
		return -1;
	}
	return 0;
}

int CDBService::Callback()
{
	return 0;
}
