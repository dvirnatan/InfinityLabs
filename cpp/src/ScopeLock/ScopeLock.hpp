#ifndef __SCOPE_LOCK_HPP__
#define __SCOPE_LOCK_HPP__

#include <boost/core/noncopyable.hpp>

namespace ilrd 
{

template <typename T>
class ScopeLock : private boost::noncopyable
{
public:
    explicit ScopeLock(T& lock, int(*unlock)(T*));
    ~ScopeLock();

private:
    T& lock;
    int(*unlock)(T*);
};

template <typename T>
ScopeLock<T>::ScopeLock(T& lock, int(*unlock)(T*)) : lock(lock), unlock(unlock)
{   
    // Empty
}

template <typename T>
ScopeLock<T>::~ScopeLock()
{
    unlock(&lock);
}

} //namespace ilrd

#endif // __SCOPE_LOCK_HPP__