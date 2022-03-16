/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~
 ~ Author        R&D 111                                       *
 * Description   singleton API                                ~
 ~ Date          10.03.2022                                    *
 * Company       ILRD Ramat Gan                                ~
 ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef ILRD__111__SINGLETON_HPP
#define ILRD__111__SINGLETON_HPP

#include <boost/core/noncopyable.hpp>   // noncopyable
#include <boost/thread/mutex.hpp> 		// boost::mutex
#include <boost/thread/lock_guard.hpp> 	// boost::lock_guard


namespace ilrd
{

using boost::mutex;
using boost::lock_guard;

template<typename T>
class Singleton : private  boost::noncopyable
{
public:
	static T& getInstance();

private:
	Singleton();
	~Singleton();
	T *m_instance;
	mutex m;
};

template<typename T>
T &Singleton<T>::getInstance()
{
	static Singleton<T> s; 
	T *tmp = s.m_instance;
	__sync_synchronize ();
	if(0 == tmp)
	{
		lock_guard<mutex> lock(s.m);

		tmp = s.m_instance;
		if(0 == tmp)
		{
			tmp = new T;
			__sync_synchronize ();
			s.m_instance = tmp;
		}
	}
	return *tmp;
}

template<typename T>
Singleton<T>::Singleton() : m_instance(0)
{

}

template<typename T>
Singleton<T>::~Singleton()
{
	delete m_instance;
}



}    // namespace ilrd

#endif    // ILRD__111__SINGLETON_HPP