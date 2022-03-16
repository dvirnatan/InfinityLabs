/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        RD111		                                     ~
 * Version       0.0.2                                           *
 ~ Date          07.03.2022                                      ~
 * Reviewer      Mr. X                                           *
 ~ Description   thread pool API                  				 ~
 * Group         R&D 111                                         *
 ~ Company       ILRD Ramat Gan                                  ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
#ifndef ILRD_111_THREAD_POOL_HPP
#define ILRD_111_THREAD_POOL_HPP

#include <boost/core/noncopyable.hpp>   // noncopyable
#include <queue>						// priority queue
#include <thread>						// thread
#include <forward_list>					// thread pool
#include <condition_variable>			// condition_variable
#include <atomic>                       // n_numofthread
		

#include "waitable_queue.hpp"			// waitable queue
#include "PQWrapper.hpp"				// PQWrapper

namespace ilrd
{

class ThreadPool : private boost::noncopyable
{

public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

	bool Finish(std::chrono::milliseconds timeout);

	enum PRIORITY { LOW, MEDIUM, HIGH };
    void AddTask(PRIORITY priority, std::function<void ()> func);
    void SetNumThreads(uint numThreads);

    void Pause();
    void Continue();

    class Task;
private:
    std::atomic<unsigned int> m_numThreads;
	void TaskHandler();

	bool m_pause = false;
	std::condition_variable run;
    std::mutex run_mutex; 

    std::condition_variable finish_cond_var;
    
    WaitableQueue< Task, PQWrapper<Task> > m_pq; 
};

} // namespace ilrd

#endif // ILRD_111_THREAD_POOL_HPP