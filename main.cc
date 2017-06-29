#include "EventMgr.h"


int main()
{
	CEventMgr evMgr;
	if(-1 == evMgr.Init())
	{
		return 0;
	}

	evMgr.Run();
	return 0;
}
