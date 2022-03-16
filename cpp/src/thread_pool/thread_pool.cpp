#include <exception>
#include <algorithm> // iterating over the list
#include <iostream> // testing and debug
#include <iterator>
#include "thread_pool.hpp"
using std::cout;
using std::endl;

namespace ilrd
{
	static const int NOW = (ThreadPool::HIGH > ThreadPool::LOW ? ThreadPool::HIGH + 1 : ThreadPool::LOW - 1);

	class CancelThreadExeption : private std::exception
	{	/* Empty */	};

	class ThreadPool::Task
	{
	public:
		explicit Task(PRIORITY priority ,std::function<void ()>func) 
		: func(func), priority(priority)
		{
			// Ctor
		}

		void RunTask()
		{
			func();
		}

		bool operator<(const Task& other) const
		{
			return (priority < other.priority);
		}

	private:
		std::function<void ()>func;
		PRIORITY priority;
	};

	void CancelTread()
	{
		throw CancelThreadExeption();   
	}

	void ThreadPool::TaskHandler()
	{	
		ThreadPool::Task todo(ThreadPool::LOW, NULL);
		while(true)
		{
			m_pq.Dequeue(&todo);
			
			if(m_pause == true)
			{
				m_pq.Enqueue(todo);
				
				while(m_pause == true)
				{
					std::unique_lock<std::mutex> lock(run_mutex);
					run.wait(lock);
				}
				m_pq.Dequeue(&todo);
			}

			try
			{
				todo.RunTask();
			}
			catch (CancelThreadExeption &e)
			{
				finish_cond_var.notify_all();
				return;
			}
		}
	}

	ThreadPool::ThreadPool(size_t numThreads) : m_numThreads(numThreads)
	{
		while(numThreads > 0)
		{
			std::thread(&ThreadPool::TaskHandler, this).detach();
			--numThreads;
		}
	}

	ThreadPool::~ThreadPool()
	{
		//cout << "Dtor ThreadPool" << endl;
	}

	bool ThreadPool::Finish(std::chrono::milliseconds timeout)
	{
		std::mutex finish_mutex; 
		std::unique_lock<std::mutex> lock(finish_mutex);
		
		Pause();
		SetNumThreads(0);
		Continue();

		while(m_numThreads > 0 )
		{
			if(std::cv_status::timeout == finish_cond_var.wait_for(lock, timeout))
			{
				return false;
			}
		}
		return true;
	}

	void ThreadPool::AddTask(PRIORITY priority, std::function<void ()> func)
	{
		m_pq.Enqueue(Task(priority, func));
	}

	void ThreadPool::SetNumThreads(uint numThreads)
	{
		while(numThreads > m_numThreads)
		{
			++m_numThreads;
			std::thread(&ThreadPool::TaskHandler, this).detach();
		}
	
		if(numThreads < m_numThreads)
		{
			Continue();
			while(numThreads < m_numThreads)
			{
				AddTask( PRIORITY(NOW), CancelTread );
				--m_numThreads;
			}
		}
		// run.notify_all();
	}

	void ThreadPool::Pause()
	{
		m_pause = true;
	}

	void ThreadPool::Continue()
	{
		m_pause = false;
		run.notify_all();
	}


}; // namespace ilrd

