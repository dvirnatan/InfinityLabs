#ifndef ILRD_RD111_FACTORY_HPP
#define ILRD_RD111_FACTORY_HPP

#include <map> // map
#include <functional> // function
#include <singleton.hpp>

namespace ilrd
{

template <class BASE, typename KEY, typename PARAM>
class Factory
{
public:
    void Add(KEY key, std::function<BASE *(PARAM p)> func);
    BASE* Create(KEY key, PARAM p) const;
private:
    std::map<KEY, std::function<BASE *()> > m_container;
    friend Singleton<Factory<BASE, KEY> >;
    Factoty();
};


}//namespace ilrd

#endif // ILRD_RD111_FACTORY_HPP