#ifndef __SERVICE_H__
#define __SERVICE_H__

#include <string>

enum class SERVICE_TYPE : public int
{
	DB = 1,
	LOGIN = 2,
};

class CService
{
public:
	CService(int serviceId);
	virtual ~CService();

public:
	virtual int Init(const char *cmd) = 0;
	virtual int Callback(int sessId, void *msg) = 0;
	virtual int Destroy() = 0;

protected:
	int m_nServiceid;
};

class CDBService : public CService
{
public:
	CDBService(int serviceId);

	~CDBService();

public:
	virtual int Init(const char *cmd) override;
	virtual int CallBack(int sessId, void *msg) override;
	virtual int Destroy() override;

private:
//	MYSQL *m_handler;
};


CService *CreateService(SERVICE_TYPE service_type)
{

}


#endif
