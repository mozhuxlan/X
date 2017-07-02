#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "Message.h"
#include <list>
#include <mutex>
#include <condition_variable>

class CQueue
{
public:
	CQueue();
	~CQueue();

	CQueue(const CQueue &rhs) = delete;
	CQueue &operator=(const CQueue &rhs) = delete;

public:
	void Push(CMessage *msg);
	CMessage *Pop();


private:
	std::mutex m_lock;
	std::condition_variable m_cond;
	std::list<CMessage *> m_list;
};


#endif
