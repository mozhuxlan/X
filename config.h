#ifndef __CONFIG_H__
#define __CONFIG_H__

class CConfig
{
public:
	CConfig() = default;
	~CConfig() = default;

public:
	int Load(const char *path);
};

#endif
