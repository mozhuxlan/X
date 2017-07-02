#include "SocketMgr.h"

int main()
{
	CSocketMgr sm;
	if(-1 == sm.InitServer("0.0.0.0", 9057))
	{
		return 0;
	}
	sm.Run();
	return 0;
}
