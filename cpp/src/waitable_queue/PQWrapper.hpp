#ifndef __PQ_WRAPPER_HPP__
#define __PQ_WRAPPER_HPP__

template <typename T> 
class PQWrapper : private std::priority_queue<T>
{
public:
    using std::priority_queue<T>::pop;
    using std::priority_queue<T>::push;
    using std::priority_queue<T>::empty;

    const T& front()
    {
        return std::priority_queue<T>::top();
    }
};

#endif // __PQ_WRAPPER_HPP__
