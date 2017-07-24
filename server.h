#ifndef __SERVER_H__
#define __SERVER_H__

#include "config.h"
#include "event.h"

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

private:
	E_SERVER_STATE m_state;
	CEventMgr m_event;
};

#endif
