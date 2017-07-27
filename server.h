#ifndef __SERVER_H__
#define __SERVER_H__

#include "config.h"
#include "event.h"
#include "service_mgr.h"

enum class E_SERVER_STATE
{
	STOP = 1,
	RUN = 2
};

class CServer
{
public:
	CServer();
	~CServer();
	CServer(const CServer &rhs) = delete;
	CServer &operator= (const CServer &rhs) = delete;

public:
	int Init(const CConfig &cfg);
	int Start();
	void Stop();
	void Destroy();

public:
	static void *StartSocket(void *arg);
	static void *StartLoop(void *arg);

private:
	E_SERVER_STATE m_state;
	CEventMgr m_event;
	CServiceMgr m_service;
	pthread_t m_threads[20];
};

#endif
