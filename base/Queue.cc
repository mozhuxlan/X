#include "Queue.h"


CQueue::CQueue()
{}

CQueue::~CQueue()
{}


void CQueue::Push(CMessage *msg)
{
	std::unique_lock<std::mutex> lock(m_lock);
	m_list.push_back(msg);
	lock.unlock();
	m_cond.notify_one();
}

CMessage *CQueue::Pop()
{
	std::unique_lock<std::mutex> lock(m_lock);
	while(m_list.empty())
	{
		m_cond.wait(lock);
	}
	CMessage *msg = m_list.front();
	m_list.pop_front();
	lock.unlock();
	return msg;
}
