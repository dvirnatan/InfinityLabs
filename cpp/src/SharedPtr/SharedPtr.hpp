#ifndef __SHARED_PTR_HPP__
#define __SHARED_PTR_HPP__

#include <cstddef>  // size_t
namespace ilrd
{

template <typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T *data = 0);
    ~SharedPtr();
    SharedPtr(const SharedPtr<T>& other);
    const SharedPtr& operator=(const SharedPtr<T>& other);

    template <typename Y>
    SharedPtr(const SharedPtr<Y>& other);

    template <typename Y>
    const SharedPtr& operator=(const SharedPtr<Y>& other);

    T *Get() const;
    operator T*() const;

    T& operator*() const;
    T* operator->() const;

private:
	void *operator new(size_t);
	void *operator new[](size_t);
	template <typename Y> friend class SharedPtr;
    T *m_data;
    size_t *m_cnt;
};

template <typename T>
bool operator==(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs);

template <typename T>
bool operator!=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs);

template <typename T>
SharedPtr<T>::SharedPtr(T *data) : m_data(data) , m_cnt(new size_t(1))
{
	// Empty
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{	
	--(*m_cnt);

	if(*m_cnt == 0)
	{
		delete m_cnt;
		delete m_data;
	}
}

template <typename T>
template <typename Y>
SharedPtr<T>::SharedPtr(const SharedPtr<Y>&other) : m_data(other.m_data), m_cnt(other.m_cnt)
{
	++(*m_cnt);
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>&other) : m_data(other.m_data), m_cnt(other.m_cnt)
{
	++(*m_cnt);
}

template <typename T>
template <typename Y>
const SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<Y>& other)
{
	SharedPtr <T> t(*this);
	--*m_cnt;
	m_cnt = other.m_cnt;
	m_data = other.m_data;
	++(*m_cnt);
	return *this;
}

template <typename T>
T *SharedPtr<T>::Get() const
{
	return m_data;
}

template <typename T>
T& SharedPtr<T>::operator*() const
{
	return *m_data;
}

template <typename T>
T* SharedPtr<T>::operator->() const
{
	return m_data;
}

template <typename T>
SharedPtr<T>::operator T*() const
{
	return m_data;
}

template <typename T>
bool operator==(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs)
{
	return (lhs.Get() == rhs.Get());
}

template <typename T>
bool operator!=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs)
{
	return !(lhs == rhs);
}


} // namespace ilrd
#endif // __SHARED_PTR_HPP__