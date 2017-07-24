#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "config.h"

int main(int argc, char *argv[])
{
	CConfig cfg;
	if(-1 == cfg.Load(argv[1]))
	{
		return 0;
	}
	CServer server;
	if(server.Init(cfg) != 0)
	{
		return 0;
	}
	server.Start();
	server.Destroy();
	return 0;
}
