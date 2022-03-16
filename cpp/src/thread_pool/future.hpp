/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        RD111		                                     ~
 * Version       0.0.2                                           *
 ~ Date          09.03.2022                                      ~
 * Reviewer      Mr. X                                           *
 ~ Description   future API		                  				 ~
 * Group         R&D 111                                         *
 ~ Company       ILRD Ramat Gan                                  ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef ILRD_111_FUTURE_HPP
#define ILRD_111_FUTURE_HPP

#include <condition_variable>	// m_condVar
#include <mutex>				// m_mutex
#include <functional>			// m_func

namespace ilrd
{

template <typename T>
class Future
{
public:
	explicit Future(std::function<T ()> func);

	void operator()();
	bool Valid() const;
	T Get();

private:
	std::function<T ()> m_func;
	T m_retVal;
	bool m_valid;
	std::mutex m_mutex;
	std::condition_variable m_condVar;
};

template <typename T>
Future<T>::Future(std::function<T ()> func) : m_func(func), m_valid(false)
{
	// Ctor
}

template <typename T>
void Future<T>::operator()()
{
	m_retVal = m_func();
	m_valid = true;
	m_condVar.notify_all();

}

template <typename T>
bool Future<T>::Valid() const
{
	return m_valid;
}

template <typename T>
T Future<T>::Get()
{
	if(! Valid())
	{
		std::unique_lock<std::mutex>lock (m_mutex);
		m_condVar.wait(lock);
	}

	return m_retVal;
}

} //namespace ilrd

#endif // ILRD_111_FUTURE_HPP