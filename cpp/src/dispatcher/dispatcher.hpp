#ifndef ILRD_RD111_DISPACHER_HPP
#define ILRD_RD111_DISPACHER_HPP


#include <set> // set
#include <functional> // std::function
#include <boost/noncopyable.hpp> // noncopyable

namespace ilrd
{
template<typename T>
class AbstractSubscriber;

template<typename T>
class Subscriber;

template<typename T>
class Dispatcher
{
public:
    explicit Dispatcher();
    ~Dispatcher();
    void Notify(const T&) const;
private:
    
    void Subscribe(AbstractSubscriber<T>& obj) ;
    void Unsubscribe(AbstractSubscriber<T>& obj);

    friend class AbstractSubscriber<T>;
    friend class Subscriber<T>;
    std::set<AbstractSubscriber<T> *> m_subs;
};

template<typename T>
class Subscriber : public AbstractSubscriber<T>
{
public:
    Subscriber(std::function<void (const T&)> update, 
                              std::function<void ()>death, Dispatcher<T>& obj);
    ~Subscriber();
private:
    std::function<void (const T&)> m_update;
    std::function<void ()> m_death;

    virtual void Update(const T& msg) const;
    virtual void Death() const;

    Dispatcher<T> *m_dispacher;
};

template <class T>
class AbstractSubscriber: private boost::noncopyable
{
private:
    AbstractSubscriber();
    virtual ~AbstractSubscriber();
    virtual void Update(const T& msg) const =0;
    virtual void Death() const =0;

    friend class Subscriber<T>;
    friend class Dispatcher<T>;
};

/*************************** Dispatcher ***************************************/

template <class T>
Dispatcher<T>::Dispatcher()
{
    // Empty
}

template <class T>
Dispatcher<T>::~Dispatcher()
{
    for(AbstractSubscriber<T> * it : m_subs)
        it->Death();
}

template <class T>
void Dispatcher<T>::Notify(const T& msg) const
{
    for(AbstractSubscriber<T> * it : m_subs)
        it->Update(msg);
}


template <class T>
void Dispatcher<T>::Subscribe(AbstractSubscriber<T>& obj)
{
    m_subs.insert(&obj);
}

template <class T>
void Dispatcher<T>::Unsubscribe(AbstractSubscriber<T>& obj)
{
    m_subs.erase(&obj);
}

/************************* AbstractSubscriber *********************************/
template <class T>
AbstractSubscriber<T>::AbstractSubscriber()
{
    // Empty
}

template <class T>
AbstractSubscriber<T>::~AbstractSubscriber()
{
    // Empty
}

/***************************** Subscriber *************************************/

template <class T>
Subscriber<T>::Subscriber(std::function<void (const T&)> update, 
                                std::function<void ()>death, Dispatcher<T> &obj)
:m_update(update),
m_death(death),
m_dispacher(&obj)
{
    m_dispacher->Subscribe(*this);
}

template <class T>
Subscriber<T>::~Subscriber()
{
    m_dispacher->Unsubscribe(*this);
}

template <class T>
void Subscriber<T>::Update(const T& msg) const
{
    m_update(msg);
}


template <class T>
void Subscriber<T>::Death() const
{
    m_death();
}


}    // namespace ilrd

#endif //ILRD_RD111_DISPACHER_HPP