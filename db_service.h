#ifndef __DB_SERVICE_H__
#define __DB_SERVICE_H__

#include <string>
#include <mysql.h>
#include "service.h"

class CDBService : public CService
{
public:
	CDBService(int serviceId);
	~CDBService();

public:
	virtual int Init(const char *param) override;
	virtual int Callback() override;

private:
	int ParseParam(const char *str);

private:
	MYSQL *m_handler;
	std::string m_host;
	int m_port;
	std::string m_username;
	std::string m_passwd;
	std::string m_db;
};

#endif
