/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        RD111		                                     ~
 * Version       0.0.1                                           *
 ~ Date          06.03.2022                                      ~
 * Reviewer      Mr. X                                           *
 ~ Description   waitable queue implementation                   ~
 * Group         R&D 111                                         *
 ~ Company       ILRD Ramat Gan                                  ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
#ifndef __WAITABLE_QUEUE_HPP_
#define __WAITABLE_QUEUE_HPP

#include <boost/core/noncopyable.hpp>   
#include <boost/chrono/duration.hpp>	
#include <boost/thread/mutex.hpp>			
#include <boost/thread/condition_variable.hpp>			
#include <queue>

namespace ilrd
{

template <class D, typename Q = std::queue<D> >
class WaitableQueue : private boost::noncopyable
{
public:
	explicit WaitableQueue();
	~WaitableQueue();

	void Enqueue(const D& data);
	void Dequeue(D *const data_out);
	bool Dequeue(D *const data_out, boost::chrono::duration<size_t, boost::milli> timeout);

private:
	Q m_queue;
	boost::mutex m_mutex; 
	boost::condition_variable m_condVar;

};
// implimitation

template <class D, typename Q>
WaitableQueue<D,Q>::WaitableQueue() 
{
	// Ctor
}

template <class D, typename Q>
WaitableQueue<D,Q>::~WaitableQueue()
{
	// Dtor
}

template <class D, typename Q>
void WaitableQueue<D,Q>::Enqueue(const D& data)
{
	{
		boost::unique_lock<boost::mutex> lock(m_mutex);
		m_queue.push(data);
	}
	m_condVar.notify_one();	
}

template <class D, typename Q>
void WaitableQueue<D,Q>::Dequeue(D *const data_out)
{
	boost::unique_lock<boost::mutex> lock(m_mutex);

	while(m_queue.empty())
	{
		m_condVar.wait(lock);
	}
 	*data_out = m_queue.front();
	m_queue.pop();
}

template <class D, typename Q>
bool WaitableQueue<D,Q>::Dequeue(D *const data_out, boost::chrono::duration<size_t, boost::milli> timeout)
{
	boost::unique_lock<boost::mutex> lock(m_mutex);

	while(m_queue.empty())
	{
		if(boost::cv_status::timeout == m_condVar.wait_for(lock, timeout))
		{
			return false;
		}
	}
	
	*data_out =	m_queue.front();
	m_queue.pop();
	
	return true;
}

} // namespace ilrd

#endif // __WAITABLE_QUEUE_HPP
