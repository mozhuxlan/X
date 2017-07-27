#ifndef __SERVICE_H__
#define __SERVICE_H__

enum class E_SERVICE_TYPE
{
	AGENT = 1,
	DB = 2
};

class CService 
{
public:
	CService(int serviceId, E_SERVICE_TYPE type) : m_serviceId(serviceId), m_type(type) {}
	virtual ~CService() {}

public:
	int GetServiceId() { return m_serviceId; }
	virtual int Init(const char *param) = 0;
	virtual int Callback() = 0;

private:
	int m_serviceId;
	E_SERVICE_TYPE m_type;
};



#endif
