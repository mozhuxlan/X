#include "EventMgr.h"


int main()
{
	CEventMgr evMgr;
	if(-1 == evMgr.InitServer("0.0.0.0", 9057))
	{
		return 0;
	}
	evMgr.Run();
	return 0;
}
